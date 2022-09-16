# Imports student data into a database.

from sys import argv, exit
from cs50 import SQL
import csv


def main():

    # check arguments
    if len(argv) != 2:
        print("Usage: python import.py characters.csv")
        exit(1)
    # get csv file path
    csv_path = argv[1]

    # set up database connection
    db = SQL("sqlite:///students.db")

    # save file contents to database
    import_csv(csv_path, db)


def import_csv(csv_path, db):
    """
    Imports contents of the csv file to database table called 'students'

    @param csv_path full path of csv file
    @param db       reference to database (cs50.sql.SQL) object
    """

    # clear entries from table, if any
    initialize_table(db)

    # parse csv file
    dbase = {}
    with open(csv_path) as data:
        reader = csv.DictReader(data)

        for row in reader:
            # get record data with required fields
            record_data = get_record_data(row)
            # insert record data into database
            insert_record(db, **record_data)


def initialize_table(db):
    """
    Clears all records from 'students' table and resets autoincremet primary key.

    @param db       reference to database (cs50.sql.SQL) object
    """

    db.execute("DELETE FROM students;")
    db.execute("DELETE FROM sqlite_sequence WHERE name='students';")


def get_record_data(row):
    """
    Returns a dictionary of fieldname-value pairs.

    @param row      dictionary from csv file with keys 'name', 'house', 'birth'
    @return         dictionary with keys 'first', 'middle', 'last', 'house', 'birth'
    """

    d = {}

    names = row['name'].split()
    d['first'] = names[0]
    d['middle'] = names[1] if len(names) == 3 else None
    d['last'] = names[2] if len(names) == 3 else names[1]
    d['house'] = row['house']
    d['birth'] = row['birth']

    return d


def insert_record(db, first=None, middle=None, last=None, house=None, birth=None):
    """
    Inserts a record into database table 'students'.

    @param db       reference to database (cs50.sql.SQL) object
    @param **args   field values
    """

    db.execute(
        """
        INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)
        """, first, middle, last, house, birth)


if __name__ == "__main__":
    main()