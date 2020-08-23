from sys import argv
from cs50 import SQL
from csv import DictReader

# check correct input
if len(argv) is not 2:
    print('input error: python import.py databases.csv')
    exit()

# open database
db = SQL("sqlite:///students.db")

# import csv to db
with open(argv[1], newline='') as csvfile:
    reader = DictReader(csvfile)
    for row in reader:

        name = row['name']
        house = row['house']
        birth = int(row['birth'])

        # split full name to first, middle and last
        name_list = name.split()
        first = name_list[0]
        last = name_list[-1]

        # check is middle name
        if len(name_list) == 2:
            middle = None
        else:
            middle = name_list[1]

        # insert every row from csv to database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)

# close csvfile
csvfile.close()
