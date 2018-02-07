####################################
# localalignment.py
#
# Author:        Juan O. Lopez
# Created:       January 12, 2018
# Last Modified: January 17, 2018
####################################

import numpy
from Bio.Seq import Seq
from Bio.Alphabet.IUPAC import unambiguous_dna

class LocalAlignment:
	# __init__
	#
	# The alphabet to be used may be specified as an argument, but unambiguous_dna ('GATC') is used as a default.
	def __init__(self, alphabet=unambiguous_dna):
	    self.alphabet = alphabet

	# loadBLASTLine
	#
	# Local alignment is populated using a line of text from a BLAST output file.
	# Fields: query id, subject id, q. start, q. end, s. start, s. end, q. seq, s. seq, evalue, bit score, score, alignment length, % identity, identical, gaps
	# Knowing this format in advance, we extract the fields of interest that are contained within each line.
	def loadBLASTLine(self, dataLine):
		la = dataLine.rstrip().split("\t") # Fields are tab-separated
		self.qId     = la[0]  # query id
		self.sId     = la[1]  # subject id
		self.qStart  = la[2]  # query start position
		self.qEnd    = la[3]  # query end position
		self.sStart  = la[4]  # subject start position
		self.sEnd    = la[5]  # subject end position
		self.qSeq    = Seq(la[6], self.alphabet)  # query sequence
		self.sSeq    = Seq(la[7], self.alphabet)  # subject sequence
		self.score   = int(la[10])
		self.aLength = int(la[11]) # alignment length
		self.numMatches = int(la[13])
		# Create a dictionary to store amount of matches per symbol
		self.matchesDict = dict()
		for i in range(self.aLength):
			if self.qSeq[i] == self.sSeq[i]:
				self.matchesDict[self.qSeq[i]] = self.matchesDict.get(self.qSeq[i],0) + 1
		# Determine the number of symbols that have matches
		self.n = len(self.matchesDict)
		# Now, for those symbols that don't have matches, store a 0
		for symbol in self.alphabet.letters:
			self.matchesDict[symbol] = self.matchesDict.get(symbol,0)

	# length
	#
	# Return the alignment length
	def length(self):
		return self.aLength

	# matches_as_list
	#
	# Returns a list that contains the amount of matches of each symbol.
	# The order in which to add the symbols is an optional parameter.
	# If not specified, then the default order of the alphabet is used.
	def matches_as_list(self, symbolOrder=None):
		if symbolOrder is None:
			symbolOrder = self.alphabet.letters
		theList = list()
		for symbol in symbolOrder:
			if symbol in self.matchesDict:
				theList.append(self.matchesDict[symbol])
		return theList

	# matches_as_dict
	#
	# Returns a dictionary that contains the amount of matches of each symbol
	def matches_as_dict(self):
		return self.matchesDict.copy()

	# matches_as_ndarray
	#
	# Returns an ndarray that contains the amount of matches of each symbol.
	# The order in which to add the symbols is an optional parameter.
	# If not specified, then the default order of the alphabet is used.
	def matches_as_ndarray(self, symbolOrder=None):
		if symbolOrder is None:
			symbolOrder = self.alphabet.letters
		return numpy.array(self.matches_as_list(symbolOrder))

	# num_matches
	#
	# If a symbol is received as a parameter, then return amount of matches for that symbol.
	# Otherwise, return total amount of matches.
	def num_matches(self, symbol=None):
		if symbol is None:
			return self.numMatches
		elif symbol in self.matchesDict:
			return self.matchesDict[symbol]
		else:
			traceback.print_stack()

	# num_symbols_matched
	#
	# Return the amount of symbols in the alphabet that have matches.
	def num_symbols_matched(self):
		return self.n

	def __repr__(self):
		return "LocalAlignment()"

	def __str__(self):
		outputStr = (self.qId + "[" + self.qStart + "-" + self.qEnd + "], "
		          + self.sId + "[" + self.sStart + "-" + self.sEnd + "]\n  "
		          + str(self.qSeq) + "\n  " + str(self.sSeq))
		return outputStr
