# common_chars_seqs.py
# Author: Juan O. Lopez (juano.lopez@upr.edu)
# Creation date:     March 29, 2018
# Modification date: March 29, 2018
#
# This program receives an input file (FASTA or text) that contains 
# the sequences that are to be compared.  The characters that are in common
# between all the sequences will be printed out to try to get an idea of
# how similar the sequences are.
#
# Since there might be a few sequences outside the norm, we'll also allow
# for some sequences to be skipped, so that we can still view the characters
# shared by most of the sequences.  To accomplish this, the program accepts
# a second optional parameter that indicates the % of commonality (lower bound)
# that is desired.  In this case, the program will loop, each time determining
# which sequence caused the most changes in the consensus string, and then
# adding that sequence to the ones to be skipped in the next iteration.  This
# continues until the % of commonality is met.  Default for this argument is 0.

from Bio.Seq import Seq
from Bio.Alphabet.IUPAC import unambiguous_dna

import sys

if len(sys.argv) < 2:
    print("Usage:", sys.argv[0], " <filename> [<commonality%>]")
    exit()

with open(sys.argv[1]) as fh:
    seqList = [ Seq(line.rstrip(),unambiguous_dna) for line in fh if not line.startswith(">") ]

if len(sys.argv) < 3:
    commPctLimit = 0
else:
    commPctLimit = float(sys.argv[2])

seqsToExclude = list() # The sequence to ignore when determining consensus
commPct = -1 # To make sure we enter the loop
while commPct < commPctLimit:
    consensus = seqList[0].tomutable()
    charsChanged = [0]*len(seqList) # How many chars changed by jth sequence
    for i in range(len(consensus)): # For each letter
        for j in range(1,len(seqList)): # Skip first sequence
            if j not in seqsToExclude and i < len(seqList[j]) and seqList[j][i] != consensus[i]:
                consensus[i] = "-"
                charsChanged[j] += 1
                break
    charsInCommon = len(consensus)-consensus.count("-")
    commPct = charsInCommon*100/len(consensus)
    if commPct < commPctLimit:
        # We haven't met the commonality percentage, so in the next iteration we will exclude
        # the sequence that caused the most changes.
        seqsToExclude.append(charsChanged.index(max(charsChanged)))
print("Sequences excluded (0-indexed):", seqsToExclude)
print("--------------------------")
print("Number of changes caused by sequences considered (# changes, # seq):")
# We'll print in descending order of values in the following format: (#changes, #seq)
charsChanged = [ (charsChanged[i], i) for i in range(len(charsChanged)) ]
print(sorted(charsChanged,reverse=True))
print("--------------------------")
print("Characters in common with all sequences (except those in \"Sequences excluded\"):")
print(consensus)
print(str(charsInCommon)+"/"+str(len(consensus)),
        "("+str(round(commPct,2))+"%)",
        str("characters in common"))
print("--------------------------")

# We want to count the ocurrences of each letter in each position, so that we
# can use the highest-occuring letter for our consensus
letterCounts = list()
for i in range(len(consensus)): # For each letter
    letterCountDict = {'A':0,'C':0,'T':0,'G':0,'X':0}
    letterCounts.append(letterCountDict)
    for j in range(len(seqList)): # For each sequence
        letterCounts[i][seqList[j][i]] += 1
for i in range(len(consensus)):
    if consensus[i] == '-':
        consensus[i] = max(letterCounts[i],key=lambda k:letterCounts[i][k])
print("Final consensus:")
print(consensus)
