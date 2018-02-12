####################################
# lastlocalalignment.py
#
# Author:        Juan O. Lopez
# Created:       January 18, 2018
# Last Modified: January 28, 2018
####################################

import numpy
from localalignment import LocalAlignment

class LASTLocalAlignment(LocalAlignment):
	def s2m_vector(self, subMatrix):
		symbols = 'ACGT' # We'll use a particular order
		r = 0
		for symbol in symbols:
			r += subMatrix[symbol]*self.num_matches(symbol)
		r -= self.score

		m = self.num_matches()
		m_v = self.matches_as_ndarray(symbols)
		v = numpy.empty(len(m_v)) # Initialized with random data
		for i in range(len(v)):
			if m_v[i] != 0:
				v[i] = m_v[i]*subMatrix[symbols[i]]/m - r/(m * self.num_symbols_matched())
			else:
				v[i] = 0
		return v

	def setDistance(self, d):
		self.distance = d # Distance to plane of perfect local alignments

	def getDistance(self):
		return self.distance

	def __repr__(self):
		return "LASTLocalAlignment()"
