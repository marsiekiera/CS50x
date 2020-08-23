from cs50 import get_int


def luhns_algorithm(number):
    number_list = list(map(int, str(number)))
    sum_luhn = 0
    for i in range(1, len(number_list) + 1):
        if i % 2 != 0:
            sum_luhn += number_list[-i]
        else:
            if number_list[-i] > 4:
                sum_luhn += 2 * number_list[-i] - 9
            else:
                sum_luhn += 2 * number_list[-i]
        i += 1
    if sum_luhn % 10 == 0:
        return True
    else:
        return False


def issuer(number):
    if number in range(4 * 10 ** 12, 5 * 10 ** 12) or number in range(4 * 10 ** 15, 5 * 10 ** 15):  # 13 or 16 digit (visa)
        return "VISA"
    elif number in range(34 * 10 ** 13, 35 * 10 ** 13) or number in range(37 * 10 ** 13, 38 * 10 ** 13):  # 15 digit (amex)
        return "AMEX"
    elif number in range(51 * 10 ** 14, 56 * 10 ** 14):  # 16 digit (master)
        return "MASTERCARD"
    else:
        return "INVALID"


def main():
    while True:
        number = get_int("Number: ")
        if number > 0:
            break
    if luhns_algorithm(number) == True:
        print(issuer(number))
    else:
        print("INVALID")


main()
