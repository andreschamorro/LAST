# extract_L1_data.py
# Author: Juan O. Lopez (juano.lopez@upr.edu)
# Creation date:     March 29, 2018
# Modification date: March 29, 2018
#
# This program receives a FASTA file as an argument (with extension .fasta)
# that contains LINE-1s, and also a CSV file with information for the
# corresponding L1s.
# The user is prompted as to which field should be extracted.  The options are:
# 5' UTR, ORF1, Inter-ORF, ORF2, and 3' UTR.
# The field headers in the CSV are fixed within this program.

import csv
import sys

if len(sys.argv) < 3:
    print("Usage:", sys.argv[0], " <filename.fasta> <L1_Data.csv>")
    exit()

fhL1s = open(sys.argv[1])
fhCSVData = open(sys.argv[2], newline='')
csvreader = csv.DictReader(fhCSVData)

option = int(input("What data should be extracted?\n" + 
      "  1) 5' UTR\n" +
      "  2) ORF1\n" +
      "  3) Inter-ORF region\n" +
      "  4) ORF2\n" +
      "  5) 3' UTR\n"+
      "Enter your choice: "))
if option < 1 or option > 5:
    exit()

fileSuffix = ["5UTR","ORF1","Inter","ORF2","3UTR"]
fhOut = open(sys.argv[1].replace(".fasta","_"+fileSuffix[option-1]+".txt"),"w")

for row in csvreader:
    fhL1s.readline() # Skip description line
    L1 = fhL1s.readline()
    # Python uses 0-indexing, but we assume the CSV uses 1-indexing
    if option == 1:
        fhOut.write(L1[:int(row["ORF1 Start"])-1]+"\n")
    elif option == 2:
        fhOut.write(L1[int(row["ORF1 Start"])-1:int(row["ORF1 End"])]+"\n")
    elif option == 3:
        fhOut.write(L1[int(row["ORF1 End"]):int(row["ORF2 Start"])-1]+"\n")
    elif option == 4:
        fhOut.write(L1[int(row["ORF2 Start"])-1:int(row["ORF2 End"])]+"\n")
    elif option == 5:
        fhOut.write(L1[int(row["ORF2 End"]):]) # Includes newline

fhL1s.close()
fhCSVData.close()
fhOut.close()
