
def makeset():
    with open("stop_words.txt", "r") as f:
        words = [ i.strip().lower() for i in f.read().split()]

        return set(words)

print(makeset())