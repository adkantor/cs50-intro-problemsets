# The program takes a sequence of DNA and a CSV file containing STR counts for a list of individuals and then output to whom the DNA (most likely) belongs.
# Usage: python dna.py data.csv sequence.txt

from sys import argv, exit
import csv
import re


def main():

    # check arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    dbfile, sequencefile = argv[1], argv[2]

    STRs, dbase = get_dbase(dbfile)
    sequence = get_sequence(sequencefile)

    # get largest number of consecutive occurrences as list
    occurrences = [number_of_consecutive_occurrences(STR, sequence) for STR in STRs]

    # find match in database
    match = match_dna(occurrences, dbase)

    # print result
    if match == None:
        print('No match')
    else:
        print(match)
    exit(0)


def get_dbase(dbfile):
    """
    Returns list of STRs and the database as dictionary, where:
        - key = name of person
        - value = list of of STR occurrences in the order of csv file

    @param dbfile   full path of csv file
    @return         list of STRs, dictionary object
    """

    dbase = {}
    with open(dbfile) as data:
        reader = csv.reader(data)

        STRs = next(reader)[1:]     # list of STRs eg. [AGAT,AATG,TATC]

        for row in reader:
            dbase[row[0]] = [int(i) for i in row[1:]]

    return STRs, dbase


def get_sequence(sequencefile):
    """
    Returns content of the txt file as string.

    @param sequencefile     full path of txt file
    @return                 string object
    """

    with open(sequencefile) as seq:
        sequence = seq.read()

    return sequence


def number_of_consecutive_occurrences(substring, full_string):
    """
    Returns nuber of consecutive occurrences of a substring in a string.

    @param substring    string we look the number of occurrences thereof
    @param full_string  string we look the number of occurrences therein
    @note:              source: https://www.quora.com/How-do-I-get-the-number-of-consecutive-occurrences-of-a-substring-in-a-string-using-Python
    """
    pattern = "((" + re.escape(substring) + ")+)"
    matches = re.findall(pattern, full_string)
    if len(matches) == 0:
        return 0
    else:
        return max(len(m[0]) // len(substring) for m in matches)


def match_dna(seq_occ, dbase):
    """
    Compares list of STR occurrences in DNA sequence to list of STR occurrences of persons in dbase.
    In case of match returns name of person.

    @param seq_occ      list of STR occurrences from sequence
    @param dbase        database as dictionary
    @return             name of person, if match found else None
    """

    for name, pers_occ in dbase.items():
        if pers_occ == seq_occ:
            return name
    return None


if __name__ == "__main__":
    main()