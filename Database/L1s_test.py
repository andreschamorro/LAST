#from Bio.Seq import Seq
from Bio import SeqIO
from Bio.SeqIO.FastaIO import SimpleFastaParser

print("SeqIO.parse with iterator example")

seqParserIter = SeqIO.parse("sequence.fasta","fasta")
for sequence in seqParserIter:
   print("Sequence ID: " + str(sequence.id))
   print("Sequence : " + sequence.seq)

print("SimpleFastaParser example")

with open("L1s.fasta") as in_handle:
    for title, seq in SimpleFastaParser(in_handle):
       print("Sequence ID: " + title)
       #print("Sequence : " + seq)
