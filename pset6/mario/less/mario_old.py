from cs50 import get_int

n = 0
while n not in range(1, 9):
    n = get_int("Height: ")

i = 0
j = 0
k = n - 1

for i in range(0, n):
    for j in range(1, n - i):
        print(" ", end="")
        j += 1
    for k in range(n - 1, n + i):
        print("#", end="")
        k += 1
    print()
    i += 1
