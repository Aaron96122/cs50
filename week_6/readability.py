def main():
    text = input("Text: ")
    letters = char_count(text)
    words = word_count(text)
    sentences = sentence_count(text)

    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # here we check the grade of text based on the index value
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def word_count(text):
    return len(text.split(" "))


def sentence_count(text):
    num = 0
    for i in range(len(text)):
        if text[i] == "." or text[i] == "?" or text[i] == "!":
            num += 1
    return num


def char_count(text):
    chars = 0
    for i in text:
        if i.isalpha():
            chars += 1
    return chars


if __name__ == "__main__":
    main()
