from cs50 import get_int

n = 0
while n not in range(1, 9):
    n = get_int("Height: ")

for i in range(0, n):
    print(" " * (n - i - 1) + "#" * (i + 1))
    i += 1
