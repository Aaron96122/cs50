from cs50 import get_string


def main():
    number = get_string("Number: ")
    while (number.isnumeric() == False):
        number = get_string("Number: ")

    valid = check(number)
    if not valid:
        print("INVALID")
    else:
        # Here we check the American Express Card Number
        if len(number) == 15 and (number[:2] in ["34", "37"]):
            print("AMEX")

        # Here we check the Master Card Number
        elif (len(number)) == 16 and (number[:2] in ["51", "52", "53", "54", "55"]):
            print("MASTERCARD")

        # Here we check the VISA Card Number
        elif len(number) in [13, 16] and (number[:1] == "4"):
            print("VISA")
        else:
            print("INVALID")


def check(number):
    # Here we set up the two lists for further check
    number = list(number)
    skip = False
    first = 0
    second = 0
    for i in range(len(number)-1, -1, -1):
        if skip:
            tmp = int(number[i]) * 2
            if len(str(tmp)) == 2:
                second += tmp // 10
                second += tmp % 10
            else:
                second += tmp
            skip = False
        else:
            first += int(number[i])
            skip = True

    # Here we check the result of the sum of first and second values
    result = first + second
    if result % 10 == 0:
        return True
    else:
        return False


if __name__ == "__main__":
    main()
