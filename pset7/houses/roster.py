from sys import argv
from cs50 import SQL

# check correct input
if len(argv) is not 2:
    print('input error: python roster.py house')
    exit()

# assign user input to a variable
user_house = argv[1]

# open database
db = SQL("sqlite:///students.db")

# export data from database
output = db.execute('SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC', user_house)

# print the result - every row in single line
for row in output:

    # check if middle name exist
    if row['middle'] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
