from Bio import SeqIO
from Bio.SeqRecord import SeqRecord
from Bio.Seq import Seq
from Bio.Alphabet import generic_dna
from numpy import random
import argparse


def main(pb, ofile):
    """TODO: Docstring for main.
    """
    choice_ltr = {"A": ["A", "C", "G", "T"],
                  "C": ["C", "A", "G", "T"],
                  "G": ["G", "A", "C", "T"],
                  "T": ["T", "A", "C", "G"]}
    cp = (1.0-pb)/3.0
    output_handle = open(ofile, "w")
    seq_sd = "".join([random.choice(choice_ltr["A"]) for x in range(6000)])
    seq_record = SeqRecord(Seq(seq_sd, generic_dna),
                           id=str(0), description="SEQ"+str(0))
    SeqIO.write(seq_record, output_handle, "fasta")

    for i in range(9):
        seq_str = "".join([random.choice(choice_ltr[l],
                                         p=[pb, cp, cp, cp]) for l in seq_sd])
        seq_record = SeqRecord(Seq(seq_str, generic_dna),
                               id=str(i+1), description="SEQ"+str(i+1))
        SeqIO.write(seq_record, output_handle, "fasta")
        pass
    pass


if __name__ == "__main__":
    optpsr = argparse.ArgumentParser(description='Gen Random DNA sequence')
    optpsr.add_argument("--prob", "-p", dest="pb", default=0.25, type=float,
                        help="Percentage of identity in decimal")
    optpsr.add_argument("--outfile", "-o", dest="output_file",
                        default="randomfile.fasta", help="Output file")
    arglt = optpsr.parse_args()
    main(arglt.pb, arglt.output_file)
