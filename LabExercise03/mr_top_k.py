from mrjob.job import MRJob
from mrjob.step import MRStep 
import re 
from heapq import nlargest 

WORD_RE = re.compile(r"[\w']+")


class MRTopK(MRJob):

    def steps(self):
        return [
            MRStep(mapper_init = self.mapper_init,
                   mapper=self.mapper_get_words,
                   combiner = self.combiner_count_words,
                   reducer=self.reducer_count_words),
            MRStep(reducer=self.reducer_find_max_word)
        ]

        
    def configure_args(self):
        """
        This method configures commandline 
        options for the program. 
        The commandline options:
            --stop-words: the name of the file 
            containing the stop words. 
        """
        super(MRTopK, self).configure_args()
        self.add_passthru_arg(
            "--top-k", default = 3,
            help = "specify the top k value. "
        )
        self.add_file_arg(
            "--stop-words", default = "def_stop_words.txt",
            help = "specify the stop words file. "
        )

    def mapper_init(self):
        """
        This method initializes or setup 
        the resources needed by the mapper function. 
        """
        file = self.options.stop_words
        self.stopwords_set = None
        with open(file, "r") as f:
            words = [ i.strip().lower() for i in f.read().split()]

        self.stopwords_set = set(words)

    def mapper_get_words(self, _, line):
        """
        This method splits every sentence from 
        the text file is split into words. All
        stop words are excuded and the finally 
        the a key-value pairs of (word, 1) are 
        returned. 
        """
        #yield each word in the line.
        for word in WORD_RE.findall(line):
            if word not in self.stopwords_set:
                yield (word.lower(), 1)

    def combiner_count_words(self, word, counts):
        """
        This method sums the number of words seen 
        so far. The number of words seen so far 
        might to be the totaal number of words 
        from the file, but the subset of the words
        from the file. 
        :param word: the key which is the word. 
        :param counts: the number of times `word`
                      appeared so far. 
        """
        #sum all the words we've seen so far
        yield(word, sum(counts))

    def reducer_count_words(self, word, counts):
        """end all(num_occurances, word) pairs to 
        the same reduce num_occurances is so  we 
        can easily use python's max() function. 
        """

        yield None, (sum(counts), word)

    def reducer_find_max_word(self, _, word_count_pairs):
        #each item of word_count_pair is (count, word)
        #so yielding one results in key=count, value=word
        yield None, word_count_pairs
        
        for count_word in word_count_pairs:
            top_k = nlargest(self.options.top_k, count_word)

        for i in range(int(self.options.top_k)):
            yield top_k

        #yield max(word_count_pairs)


if __name__=="__main__":
     MRTopK.run()