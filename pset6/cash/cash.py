from cs50 import get_float

while True:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        break

cents = dollars * 100
quaters = cents // 25
cents -= quaters * 25
dimes = cents // 10
cents -= dimes * 10
nickels = cents // 5
cents -= nickels * 5
pennies = cents // 1

print(int(quaters + dimes + nickels + pennies))
