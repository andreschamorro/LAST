# column_analyzer.py
# Author: Juan O. Lopez (juano.lopez@upr.edu)
# Creation date:     April 16, 2018
# Modification date: April 16, 2018
#
# This program receives an input file (FASTA or text) that contains 
# the sequences that are to be compared.  The user is repeatedly prompted
# for a column number, and a count of the letters for that column is
# printed.  The program ends when a 0 is entered for column number.

from Bio.Seq import Seq
from Bio.Alphabet.IUPAC import unambiguous_dna

import sys

if len(sys.argv) < 2:
    print("Usage:", sys.argv[0], " <filename>")
    exit()

with open(sys.argv[1]) as fh:
    seqList = [ Seq(line.rstrip(),unambiguous_dna) for line in fh if not line.startswith(">") ]

print("There are", len(seqList), "sequences.")
while True:
    colToProcess = int(input("Enter column number to analyze (0 to exit): "))
    if colToProcess == 0:
        break

    # Count ocurrences of each letter in the column specified by the user
    letterCountDict = {'A':0,'C':0,'T':0,'G':0,'X':0}
    colToProcess -= 1 # Python uses 0-indexing
    for i in range(len(seqList)):
        if colToProcess < len(seqList[i]):
            letterCountDict[seqList[i][colToProcess]] += 1
    print(letterCountDict)
    rowsAccounted = sum(letterCountDict.values())
    if rowsAccounted < len(seqList):
        print(len(seqList)-rowsAccounted,"sequences have less than",colToProcess+1,"columns.")
