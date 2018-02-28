# Module : ShinkageClustering
# A fasta and size-constrained clustering algorithm for
# biomedica applications
#  The implementation is based on the first of those described in the
#  following paper:
#
# Author    : Andres Chamorro
# Email     : andres.chamorro@upr.edu
#
#    * Chenyue W.Hu, Hanyang Li and Amina A. Qutub
#    \"/Shinkage Clustering: A fast and size-constrained clustering algorithm
#     for biomedical applications/\", BMC Bioinformatics 2018 19:19,
#    DOI 10.1186/s12859-018-2022-8
# Input : S_{N\timesN} Similarity matrix
#         K_0 Initial number of clusters
import numpy


def convert(data):
    """Decode bytes data.

    :data: byte data
    :returns: decode data

    """
    if isinstance(data, bytes):
        return data.decode()
    if isinstance(data, (str, int)):
        return str(data)
    if isinstance(data, dict):
        return dict(map(convert, data.items()))
    if isinstance(data, tuple):
        return tuple(map(convert, data))
    if isinstance(data, list):
        return list(map(convert, data))
    if isinstance(data, set):
        return set(map(convert, data))


def drop_zero_columns(M):
    """Remove empty columns.

    :M: numpy matrix
    :returns: M whitout empty columns

    """
    if isinstance(M, numpy.ndarray):
        M = numpy.delete(M, numpy.where(numpy.sum(M, 0) == 0), 1)
        pass
    return M
    pass


def seqdisH(seqX, seqY):
    """Hamming slide windows distance.

    :seqX: String
    :seqY: String
    :returns: distance

    """
    seqmin = min([seqX, seqY], key=len)
    seqmax = max([seqX, seqY], key=len)
    diff = len(seqmax) - len(seqmin)
    s2s = [seqmax[i:len(seqmin)+i] for i in range(diff+1)]
    hd = min([sum(c1 != c2 for c1, c2 in zip(seqmin, s2)) for s2 in s2s])
    return(1.0-hd/len(seqmin))
    pass


def assemblySim(csvfile):
    """Assembly similarity matrix from csv file.
    Xi, Xj, XiStar, XiEnd, XjStar, XjEnd
    U, U, int, int, int, int, U, U

    :cvsfile: TODO
    :returns: Similarity Matrix, Index label dict

    """
    # Get the data in file
    alings = numpy.genfromtxt(
        csvfile,
        delimiter=',',
        skip_header=0,
        names=True,
        dtype=None)
    labeldict = dict()
    for a in alings:
        if (a[0] in labeldict):
            labeldict[a[0]].append(a[6])
            pass
        else:
            labeldict[a[0]] = [a[6]]
            pass
        pass
        if (a[1] in labeldict):
            labeldict[a[1]].append(a[7])
            pass
        else:
            labeldict[a[1]] = [a[7]]
            pass
        pass
    labeldict = convert(labeldict)
    es = numpy.array([e.replace('-', '')
                      for a in labeldict.values() for e in a])
    S = numpy.array([seqdisH(x, y)
                     for x in es for y in es]).reshape(es.size, es.size)
    return(S, labeldict)
    pass


def shC(S, K0, eps=1.0e-6, maxiter=500):
    """Shrinkage Clustering: Base Algorithm.

    :S: Similarity Matrix
    :K0: Initial number of clusters
    :eps: Tolerance
    :maxiter: Max number of iterations
    :returns: cluster assignment

    """
    # Generate a random A_{N\timesK0} Cluster assigment matrix
    N, _ = S.shape
    A = numpy.zeros((N, K0))
    for i in range(N):
        j = numpy.random.randint(K0)
        A[i, j] = 1
    pass
    v = numpy.ones(N)
    St = 1 - 2*S
    it = 0
    while it < maxiter:
        # Remove empty clusters
        A = drop_zero_columns(A)
        NA, KA = A.shape
        # Permute the cluster membership that minimizes objetive function
        M = numpy.dot(St, A)
        # Gready choice
        v = numpy.min(M, 1) - numpy.sum(numpy.multiply(M, A), 1)
        Xb = numpy.argmin(v)
        # Permute the membership of Xb to Cp
        jdex = numpy.array([j for j in range(KA) if j != Xb])
        Cp = jdex[numpy.argmin(M[Xb, jdex])]
        A[Xb, ] = 0
        A[Xb, Cp] = 1
        if (abs(numpy.sum(v)) < eps):
            print(it)
            break
        it += 1
        pass
    return(A)
    pass
