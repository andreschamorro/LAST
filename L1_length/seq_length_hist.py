# seq_length_hist.py
# Author: Juan O. Lopez (juano.lopez@upr.edu)
# Creation date:     March 24, 2018
# Modification date: March 30, 2018
#
# This program receives an input file (FASTA or text) as an argument
# and generates a histogram of the lengths of the sequences.
# Sometimes the extrema render the graph useless because the data is
# spread out too thin.  That's why we also allow the user to specify how
# many length entries should be skipped at the start and at the end.

import matplotlib.pyplot as plt

import os
import sys

# Default values in case arguments are not used
SKIPATSTART = 0
SKIPATEND = 0

if len(sys.argv) < 2:
    print("Usage:", sys.argv[0], " <filename> [<numSkipStart> <numSkipEnd>]")
    exit()
elif len(sys.argv) == 4:
    SKIPATSTART = int(sys.argv[2])
    SKIPATEND = int(sys.argv[3])

# Read the sequences from the input file and store the lengths in a list
filename = sys.argv[1]
with open(filename) as fh:
    lengthList = [ len(line) for line in fh if not line.startswith(">") ]

# We print the "histogram" to an output text file before we display the graph.
# Output file will have the same name as the input file, but we'll add
# "_length" at the end.
myHist = dict()
for l in lengthList:
    myHist[l] = myHist.get(l,0) + 1
fh = open(os.path.splitext(sys.argv[1])[0]+"_length.txt","w")
for key in sorted(myHist.keys()):
    fh.write(str(key) + ": " + str(myHist[key])+"\n")
fh.close()

# Now we generate and display the graph
lengthList.sort()
N, bins, patches = plt.hist(lengthList, bins='auto', range=(lengthList[SKIPATSTART],lengthList[len(lengthList)-1-SKIPATEND]))
plt.gca().minorticks_on()
plt.title(sys.argv[1])
# We'll save the graph to the same name as the text file, but .png
plt.savefig(os.path.splitext(sys.argv[1])[0]+"_length.png")
plt.show()
