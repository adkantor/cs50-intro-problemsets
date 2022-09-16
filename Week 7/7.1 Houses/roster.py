# Prints a list of students for a given house in alphabetical order.

from sys import argv, exit
from cs50 import SQL


def main():

    # check arguments
    if len(argv) != 2:
        print("Usage: python roster.py HouseName")
        exit(1)
    # get csv file path
    house_name = argv[1]

    # set up database connection
    db = SQL("sqlite:///students.db")

    # print data
    print_roster(db, house_name)

    exit(0)


def print_roster(db, house_name):
    """
    Prints a list of students for a given house in alphabetical order.

    @param db           reference to database (cs50.sql.SQL) object
    @param house_name   name of house to query
    """

    sql_string = "SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC"

    # run qery
    result = db.execute(sql_string, house_name)

    # parse results
    for row in result:
        print_student(row)


def print_student(row):
    """
    Prints name and birth year of a student.

    @param row  dictionary with record data
    """
    first, middle, last = row['first'], row['middle'], row['last']

    name = " ".join((first, middle, last)) if middle != None else " ".join((first, last))
    born = row['birth']
    print('{}, born {}'.format(name, born))


if __name__ == "__main__":
    main()
