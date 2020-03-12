from mrjob.job import MRJob 
from mrjob.step import MRStep 
import re 
import os 

WORD_RE = re.compile(r"[\w']+")

class MRWordCount(MRJob):

    def configure_args(self):
        super(MRWordCount, self).configure_args()
        self.add_passthru_arg(
            "--stop-words", default = "def_stop_words.txt",
            help = "specify the stop words file. "
        )

    def mapper_init(self):
        self.stop_words_set = None 
        stop_words_file = self.options.stop_words
        with open("/home/user/Desktop/Ashesi/2020/parallel-distributed-computing/LabExercise03/" + stop_words_file, "r") as f:
            words = [ i.strip().lower() for i in f.read().split()]

        self.stop_words_set =  set(words)

    def mapper(self, _, line):

        #yield each non stopword in the line.
        for word in WORD_RE.findall(line):
            if word not in self.stop_words_set:
                yield (word.lower(), 1)

    def reducer(self, word, counts):
        #sum all the words we've seen so far
        yield(word, sum(counts))

if __name__ == "__main__":
    MRWordCount.run()