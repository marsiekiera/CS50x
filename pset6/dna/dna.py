# Version 1.1
# import modules
from sys import argv
from csv import DictReader, reader


def column_list(file):
    # create list of columns named 'columns'- first row from database file
    with open(file, newline='') as csvfile:
        csv_reader = reader(csvfile)
        columns = next(csv_reader)
    csvfile.close()
    # remove 'name' column from columns list
    columns.pop(0)
    return columns


def names_list(file):
    # create list of dictionary named 'names'
    names = []
    with open(file, newline='') as csvfile:
        reader = DictReader(csvfile)
        for row in reader:
            names.append(row)
    csvfile.close()
    return names


def sequence_string(file):
    # create string sequence contain dna sequence
    with open(file, 'r') as f_sequence:
        sequence = f_sequence.read()
    f_sequence.close()
    return sequence


def counting_function(columns, sequence):
    # function couting max length of each STR
    # create empty dict
    count = {}
    for i in range(0, len(columns)):
        if columns[i] in sequence:
            str_temp = str(columns[i])
            while True:
                if str_temp not in sequence:
                    break
                else:
                    str_temp += str(columns[i])
            count[columns[i]] = int(len(str_temp) / len(str(columns[i])) - 1)
        else:
            print('No match')
            exit()
    return count


def match(names, columns, count):
    for i in range(0, len(names)):
        counter = 0
        for j in range(0, len(columns)):
            if int(names[i][columns[j]]) == count[columns[j]]:
                counter += 1
            if counter == len(columns):
                return names[i]['name']
            if i == len(names) - 1 and j == len(columns) - 1 and counter < len(columns):
                return 'No match'


def main():
    if len(argv) is not 3:
        return 'input error: python dna.py databases.csv sequences.txt'
    columns = column_list(argv[1])
    names = names_list(argv[1])
    sequence = sequence_string(argv[2])
    count = counting_function(columns, sequence)
    return match(names, columns, count)


print(main())
