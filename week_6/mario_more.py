from cs50 import get_int


def main():
    number = get_int("Height: ")
    while number < 1 or number > 8:
        number = get_int("Height: ")
    else:
        for i in range(1, number + 1):
            print(" " * (number - i) + "#" * i + "  " + "#" * i)


if __name__ == "__main__":
    main()
