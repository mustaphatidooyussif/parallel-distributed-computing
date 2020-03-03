from mrjob.job import MRJob 
from mrjob.step import MRStep 
import re 
import os 

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
def makeset():
    #read and convert stop words to a set
    #make sure the stop words file is in the same directory. 
    with open("stop_words.txt", "r") as f:
        words = [ i.strip().lower() for i in f.read().split()]
            
        return set(words)

class MRWordCount(MRJob):

    def mapper(self, _, line):

        #yield each non stopword in the line.
        for word in WORD_RE.findall(line):
            if word not in stop_words:
                yield (word.lower(), 1)

    def reducer(self, word, counts):
        #sum all the words we've seen so far
        yield(word, sum(counts))

if __name__=="__main__":
    MRWordCount.run()