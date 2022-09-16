# Houses

Implement a program to import student data into a database, and then produce class rosters.
```
$ python import.py characters.csv
$ python roster.py Gryffindor
Lavender Brown, born 1979
Colin Creevey, born 1981
Seamus Finnigan, born 1979
Hermione Jean Granger, born 1979
Neville Longbottom, born 1980
Parvati Patil, born 1979
Harry James Potter, born 1980
Dean Thomas, born 1980
Romilda Vane, born 1981
Ginevra Molly Weasley, born 1981
Ronald Bilius Weasley, born 1980
```


## Specification
In ```import.py```, write a program that imports data from a CSV spreadsheet.
- Your program should accept the name of a CSV file as a command-line argument.
    - If the incorrect number of command-line arguments are provided, your program should print an error and exit.
    - You may assume that the CSV file will exist, and will have columns ```name```, ```house```, and ```birth```.
- For each student in the CSV file, insert the student into the students table in the ```students.db``` database.
    - While the CSV file provided to you has just a name column, the database has separate columns for first, middle, and last names. You?ll thus want to first parse each name and separate it into first, middle, and last names. You may assume that each person?s name field will contain either two space-separated names (a first and last name) or three space-separated names (a first, middle, and last name). For students without a middle name, you should leave their middle name as NULL in the table.

In ```roster.py```, write a program that prints a list of students for a given house in alphabetical order.
- Your program should accept the name of a house as a command-line argument.
    - If the incorrect number of command-line arguments are provided, your program should print an error and exit.
    - Your program should query the students table in the ```students.db``` database for all of the students in the specified house.
    - Your program should then print out each student?s full name and birth year (formatted as, e.g., ```Harry James Potter, born 1980``` or ```Luna Lovegood, born 1981```).
    - Each student should be printed on their own line.
    - Students should be ordered by last name. For students with the same last name, they should be ordered by first name.