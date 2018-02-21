from Bio.Seq import Seq
from Bio.Alphabet.IUPAC import unambiguous_dna

import random
import argparse

SEQCOUNT = 500
SEQLENGTH = 6000

def main(pctToPreserve, ofile):
	"""Main function that gets called initially with command-line arguments."""
	pctToChange = 1.0 - pctToPreserve
	textFile= open(ofile,"w")
	randSeq = "".join([random.choice(unambiguous_dna.letters) for x in range(SEQLENGTH)])
	seqBase = Seq(randSeq, unambiguous_dna)
	textFile.write(">SEQ0\n"+str(seqBase))
    
	for i in range(1,SEQCOUNT):
		seqCopy = change_seq_by_pct(seqBase, pctToChange)
		textFile.write("\n>SEQ" + str(i) + "\n" + str(seqCopy))
	textFile.close()

def change_seq_by_pct(seqOrig, pct):
	"""Return a modified copy of sequence by changing pct % of its symbols."""
	# We use a dictionary to indicate the possible substitutions for each symbol.
	substOptions = {"A": ["C", "G", "T"],
	                "C": ["A", "G", "T"],
	                "G": ["A", "C", "T"],
	                "T": ["A", "C", "G"]}
	seqChanged = seqOrig.tomutable() # Use MutableSeq for convenience of modifying
	seqLen = len(seqChanged)
	amtToChange = int(seqLen * pct)
	# We use random sampling to determine the positions that will be changed
	posToChange = random.sample(range(seqLen), amtToChange)

	for i in posToChange:
		seqChanged[i] = random.choice(substOptions[seqChanged[i]])

	#DEBUG TEST
	charsChanged = sum (1 for x, y in zip(str(seqOrig), str(seqChanged)) if x != y)
	if charsChanged != amtToChange:
		print ("charsChanged =", charsChanged, ", amtToChange =", amtToChange)
	#END DEBUG

	return seqChanged

if __name__ == "__main__":
	# Parse command-line arguments and pass them to main function.
	optpsr = argparse.ArgumentParser(description='Gen Random DNA sequence')
	optpsr.add_argument("--prob", "-p", dest="pb", default=0.25, type=float,
	                       help="Percentage of identity in decimal")
	optpsr.add_argument("--outfile", "-o", dest="output_file",
	                       default="randomfile.fasta", help="Output file")
	arglt = optpsr.parse_args()
	main(arglt.pb, arglt.output_file)
