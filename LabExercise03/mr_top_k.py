from mrjob.job import MRJob
from mrjob.step import MRStep 
import re 

WORD_RE = re.compile(r"[\w']+")


stop_words ={'be', 'he', 'same', 'before', 'we', 'was', 'as', 
            'out', 'hers', 'over', 'having', 'for', 'i', 'nor', 
            'on', 'very', 'himself', 'now', 'she', 'until', 'are', 
            'is', 'if', 'do', 'more', 'should', 'in', 'when', 
            'these', 'between', 'to', 'our', 'which', 'or', 'off', 
            'you', 'such', 'at', 'his', 'of', 'during', 'further', 
            'so', 'by', 'where', 'ours', 'theirs', 'few', 'some', 
            'a', 'about', 'yourselves', 'not', 'up', 'been', 'because',
             'how', 'themselves', 'her', 'and', 'being', 'then', 
             'did', 'why', 'all', 'both', 'but', 'itself', 'the', 
             'under', 'too', 'yours', 'its', 'have', 'most', 'above', 
             'down', 'only', 'my', 'from', 'me', 'this', 'here', 'whom', 
             'yourself', 'through', 'am', 'has', 'while', 'herself', 
             'other', 'them', 'what', 'just', 'there', 'than', 'can',
              'any', 'don', 'myself', 'that', 'no', 'who', 'each', 'will',
               'him', 'it', 'their', 'below', 'own', 'had', 'after', 
               'ourselves', 'into', 'doing', 'they', 'those', 'your',
                'against', 'again', 'with', 'once', 'were', 'does', 'an'}

class MRTopK(MRJob):

    def steps(self):
        return [
            MRStep(mapper=self.mapper_get_words,
                   combiner = self.combiner_count_words,
                   reducer=self.reducer_count_words),
            MRStep(reducer=self.reducer_find_max_word)
        ]

    def mapper_get_words(self, _, line):
        #yield each word in the line.
        for word in WORD_RE.findall(line):
            if word not in stop_words:
                yield (word.lower(), 1)

    def combiner_count_words(self, word, counts):
        #sum all the words we've seen so far
        yield(word, sum(counts))

    def reducer_count_words(self, word, counts):
        #send all(num_occurances, word) pairs to the same reduce
        #num_occurances is so  we can easily use python's max() function. 

        yield None, (sum(counts), word)

    def reducer_find_max_word(self, _, word_count_pairs):
        #each item of word_count_pair is (count, word)
        #so yielding one results in key=count, value=word
        yield max(word_count_pairs)


if __name__=="__main__":
     MRTopK.run()