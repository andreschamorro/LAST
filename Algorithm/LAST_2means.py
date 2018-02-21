# last_alg.py
#
# Author:        Juan O. Lopez
# Created:       January 10, 2018
# Last Modified: February 17, 2018

import glob
import pathlib

import matplotlib.pyplot as plt
from matplotlib.ticker import FixedLocator, ScalarFormatter
import numpy as np
from scipy.cluster.vq import kmeans2

from lastlocalalignment import LASTLocalAlignment

# This is the default "substitution matrix" for BLAST
# (For DNA it actually uses single values for reward and penalty scores)
sub_matrix = [[2, -3, -3, -3], \
              [-3, 2, -3, -3], \
              [-3, -3, 2, -3], \
              [-3, -3, -3, 2]]
amtCentroids = 2 # Amount of centroids to be generated with k-means algorithm
# Note that the code for the histogram currently assumes 2 centroids!

S = dict()
index = 0
for symbol in ['G', 'A', 'C', 'T'] : # We assume 'GACT' order...
    # We're only interested in matches, so we only look at the diagonal
    S[symbol] = sub_matrix[index][index]
    index += 1
# z represents a vector perpendicular to our plane of "perfect matches"
z = np.array([1, S['A']/S['C'], S['A']/S['G'], S['A']/S['T']])
normOfZ = np.linalg.norm(z) # To avoid calculating every time
#normOfZSquared = normOfZ * normOfZ

la_list = list()
# la_dict will be used as a matrix where you first use the query id as
# index, and then the subject id as index.
la_dict = dict()

#for filename in glob.glob("Output/blastnSearchOutput_3.txt"):
for filename in glob.glob("Output/*.txt"):
	try:
		fh = open(filename)
	except:
		print("ERROR: Could not open file", filename)
		exit()

	tempList = list()
	for line in fh:
		if line[0] == "#": # Skip comment lines
			continue
		myLa = LASTLocalAlignment()
		myLa.loadBLASTLine(line)
		tempList.append(myLa)
		if myLa.qId not in la_dict:
			la_dict[myLa.qId] = dict()
		if myLa.sId not in la_dict:
			la_dict[myLa.sId] = dict()
		if myLa.sId not in la_dict[myLa.qId]:
			la_dict[myLa.qId][myLa.sId] = list()
		if myLa.qId not in la_dict[myLa.sId]:
			# la_dict[a,b] should reference the same list as la_dict[b,a]
			la_dict[myLa.sId][myLa.qId] = la_dict[myLa.qId][myLa.sId]
		la_dict[myLa.qId][myLa.sId].append(myLa)

	la_list += tempList
	fh.close()

for i in range(len(la_list)):
	b = la_list[i].s2m_vector(S) # Vector representation of LA
	bDotZ = b@z
	#coefficient = (S['A'] - bDotZ)/normOfZSquared
	distance = (S['A'] - bDotZ)/normOfZ
	la_list[i].setDistance(distance)

# Use the 2-means algorithm to generate centroids.
la_list.sort(key=lambda l:l.getDistance())
distList = [ la.getDistance() for la in la_list ]
centroids, labels = kmeans2(distList, amtCentroids)
centroids.sort() # For some reason, sometimes they are unsorted
labels.sort()
amtCentroid0 = np.searchsorted(labels, 1) # Our histogram currently assumes 2 centroids!

# Store each distance and score-to-matches ratio for clustering.
# We will use a separate file for the LAs of each centroid.
i = 0
curCentroid = 0
pathlib.Path('distances').mkdir(exist_ok=True) # Create dir if doesn't exist
while i < len(labels): # Note that labels and distList have the same length
	fOut = open("distances/distancesCl"+str(curCentroid)+".txt", "w")
	fOut.write(str(S['A'])+"\n") # Using same reward score for all symbols, so store only once in file
	while i < len(labels) and labels[i] == curCentroid:
		la = la_list[i]
		# CSV: qId, sId, qStart, qEnd, sStart, sEnd, distance(A) to P, rho(A)
		fOut.write(",".join([la.qId,la.sId,la.qStart, la.qEnd, la.sStart, la.sEnd, str(la.getDistance()),str(la.score/la.num_matches())])+"\n")
		i += 1
	fOut.close()
	curCentroid += 1

# Draw a histogram of the distances to the plane of "perfect matches"
N, bins, patches = plt.hist(distList, bins='auto')
# Use different colors for the bins that "belong" to different clusters.
# We can't draw a bin with 2 different colors, so "middle" bin won't be 100% correctly colored.
# NOTE: THIS HISTOGRAM CURRENTLY ASSUMES 2 CENTROIDS!
cntCluster1 = 0
cntCluster2 = 0
for i in range(len(patches)):
	if cntCluster1 < amtCentroid0:
		patches[i].set_facecolor('b')
		cntCluster1 += N[i]
	else:
		patches[i].set_facecolor('g')
		cntCluster2 += N[i]

# Add red vertical lines at the positions of the centroids.
for i in range(len(centroids)):
	plt.axvline(x=centroids[i], color='r')

# Add red ticks with red labels to the centroids, to show their values.
# We do that by using "minor ticks" and formatting them.
ax = plt.gca() # Get the current Axes instance
ax.xaxis.set_minor_locator(FixedLocator(list(centroids))) # Minor ticks at fixed positions
ax.xaxis.set_minor_formatter(ScalarFormatter()) # No formatting; just display the value
ax.xaxis.set_tick_params(color='r', pad=15, which='minor')
plt.setp(ax.xaxis.get_minorticklabels(), color='r')

# Set axis labels, figure title, save figure, and display it.
plt.title("Histogram of distance of LAs to plane of perfect matches\nwith clustering using 2-means algorithm")
plt.xlabel("Distance")
plt.ylabel("Amount of LAs")
plt.savefig("distances/distances.png")
plt.show()
exit() 

#====================================================================
# CODE BELOW IS CURRENTLY NOT BEING EXECUTED, BUT LEFT FOR REFERENCE
#====================================================================

# It would be insightful to create a separate histogram (and distance file) for
# each sequence, taking into consideration the local alignments it participates in.
laCnt = 1
for key1 in sorted(la_dict):
	# First we create a sublist of all LAs that involve the sequence in key1
	la_sublist = list()
	for key2 in la_dict[key1]:
		la_sublist += la_dict[key1][key2]
	# Now we sort that list by distance to the "perfect local alignment plane"
	la_sublist.sort(key = lambda l:l.getDistance())

	fOut = open("distances/distance" + str(laCnt) + ".txt", "w")
	distList = list()
	for la in la_sublist:
		fOut.write("d(" + la.qId + "," + la.sId + ") = " + str(la.getDistance()) + "\n") 
		distList.append(la.getDistance())
	fOut.close()
	plt.hist(distList, bins='auto')
	plt.title("Histogram of distance of " + key1 + " LAs to plane")
	plt.savefig("distances/distance" + str(laCnt) + ".png")
	laCnt += 1
