from mr_word_count import MRWordCount 
from mr_top_k import MRTopK 
import sys 

##set up command line arguements here... 

def labExercise3(job, topk = 4):
    if job == "count":
        print("do word count")
    elif job = "topk":
        print("run top k")
    else:
        print("program not supported")


if __name__=="__main__":
    job = sys.arg[1]
    k = sys.arg[2]
    labExercise3(job, k)