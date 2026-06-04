def main():
    number = input("Height: ")
    while number.isnumeric() == False or int(number) < 1 or int(number) > 8:
        print("please type in a number between 1 and 8, inclusive")
        number = input("Height: ")
    else:
        number = int(number)
        for i in range(1, number + 1):
            print(" " * (number - i) + "#" * i)


if __name__ == "__main__":
    main()
