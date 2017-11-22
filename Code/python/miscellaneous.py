from Bio import AlignIO
import collections, numpy
from scipy.special import binom

def blosumMat(filename, filetype, ignoreline=[], printer=True):
    in_handle = open(filename)
    alignment = AlignIO.read(in_handle, filetype)
    align_array_t = numpy.array([list(rec) for rec in alignment if rec.id not in ignoreline], numpy.character).T
    
    numblock = 0
    
    Cij = numpy.zeros((4, 4))
    for col in align_array_t:
        Cijk = numpy.zeros((4, 4))
        counter = collections.Counter(col)
        if counter[b'-'] == 0:
            numblock += 1
            Cijk[0, :] = counter[b'A']*numpy.array([counter[b'A'],counter[b'C'],counter[b'G'],counter[b'T']])
            Cijk[1, :] = counter[b'C']*numpy.array([counter[b'A'],counter[b'C'],counter[b'G'],counter[b'T']])
            Cijk[2, :] = counter[b'G']*numpy.array([counter[b'A'],counter[b'C'],counter[b'G'],counter[b'T']])
            Cijk[3, :] = counter[b'T']*numpy.array([counter[b'A'],counter[b'C'],counter[b'G'],counter[b'T']])
            Cijk[0, 0] = binom(counter[b'A'], 2)
            Cijk[1, 1] = binom(counter[b'C'], 2)
            Cijk[2, 2] = binom(counter[b'G'], 2)
            Cijk[3, 3] = binom(counter[b'T'], 2)
        Cij += Cijk
    T = numpy.sum(numpy.triu(Cij))
    Q = Cij/T
    P = numpy.zeros((4, 1))
    P[0] = Q[0, 0] + 0.5*Q[0, 1] + 0.5*Q[0, 2] + 0.5*Q[0, 3]
    P[1] = Q[1, 1] + 0.5*Q[0, 0] + 0.5*Q[0, 2] + 0.5*Q[0, 3]
    P[2] = Q[2, 2] + 0.5*Q[0, 0] + 0.5*Q[0, 1] + 0.5*Q[0, 3]
    P[3] = Q[3, 3] + 0.5*Q[0, 0] + 0.5*Q[0, 1] + 0.5*Q[0, 2]
    
    E = numpy.zeros((4, 4))
    
    E = 2.0*numpy.matmul(P, P.T)
    
    E[0, 0] = P[0]*P[0]
    E[1, 1] = P[1]*P[1]
    E[2, 2] = P[2]*P[2]
    E[3, 3] = P[3]*P[3]
    
    S = numpy.log2(Q/E)
    B = numpy.round(2.0*S)
    
    if printer:
        print(S)
        print(B)
        print("Number of block alignments %i" % numblock)
