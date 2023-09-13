# Moshe Rubin
# 2/3/2021
# Coleman-Liau readability formula
# https://cs50.harvard.edu/x/2021/psets/6/readability/

def main():
    text = input("Text: ")
    index = coleman_liau(text)
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")
        

def count_letters(text):
    count = 0
    for letter in text:
        if letter.isalpha():
            count += 1
    return count


def count_words(text):
    count = 0
    for letter in text:
        if letter == " ":
            count += 1
    return count + 1


def count_sentences(text):
    count = 0
    for letter in text:
        if letter in ['.', '!', '?']:
            count += 1
    return count


def coleman_liau(text):
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    
    # index = 0.0588 * L - 0.296 * S - 15.8
    # L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    L = letters / (words / 100)
    S = sentences / (words / 100)
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index
    

if __name__ == "__main__":
    main()
    