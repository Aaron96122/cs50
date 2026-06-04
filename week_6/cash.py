from cs50 import get_float


def main():
    change = get_float("Change: ")
    while change < 0:
        change = get_float("Change: ")
    else:
        change = change * 100
        number = 0
        for currency in [25, 10, 5, 1]:
            temp = change // currency
            number += temp
            change -= currency * temp
    print(int(number))


if __name__ == "__main__":
    main()
