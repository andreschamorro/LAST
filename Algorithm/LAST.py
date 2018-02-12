# last_alg.py
#
# Author:        Juan O. Lopez
# Created:       January 10, 2018
# Last Modified: January 29, 2018

import glob

import matplotlib.pyplot as plt
import numpy

from lastlocalalignment import LASTLocalAlignment

# This is the default substitution matrix for BLAST
sub_matrix = [[5, -4, -4, -4], \
              [-4, 5, -4, -4], \
              [-4, -4, 5, -4], \
              [-4, -4, -4, 5]]
S = dict()
index = 0
for symbol in ['G', 'A', 'C', 'T'] : # We assume 'GACT' order...
    # We're only interested in matches, so we only look at the diagonal
    S[symbol] = sub_matrix[index][index]
    index += 1
z = numpy.array([1, S['A']/S['C'], S['A']/S['G'], S['A']/S['T']])
normOfZ = numpy.linalg.norm(z) # To avoid calculating every time
normOfZSquared = normOfZ * normOfZ

la_list = list()
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
		if line[0] == "#":
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
			la_dict[myLa.sId][myLa.qId] = la_dict[myLa.qId][myLa.sId] # la_dict[a,b] should reference the same list as la_dict[b,a]
		la_dict[myLa.qId][myLa.sId].append(myLa)
		#print(myLa)

#	print("There are a total of", len(tempList), "local alignments in", filename)
	la_list += tempList
	fh.close()

print("There are a total of", len(la_list), "local alignments.")

# Print out the amount of alignments between every different pair of strings
#for key1 in sorted(la_dict):
#	for key2 in sorted(la_dict[key1]):
#		if key1 < key2: # This avoids duplicating the information since the dictionary is "symmetric"
#			print("la_dict[",key1,"][",key2,"] has ", len(la_dict[key1][key2]),"alignments")

for i in range(len(la_list)):
	#print(la_list[i].matches_as_dict()) #DEBUG
	b = la_list[i].s2m_vector(S)
	#print("b=",b) #DEBUG
	#print("b@z=",b@z) #DEBUG
	bDotZ = b@z
	alpha = (S['A'] - bDotZ)/normOfZSquared
	distance = (S['A'] - bDotZ)/normOfZ
	la_list[i].setDistance(distance)
	#print("alpha=",alpha) #DEBUG
	#print("distance=",distance) #DEBUG
	#print("----------------------") #DEBUG

# OLD 'histogram' code (done manually)
la_list.sort(key = lambda l:l.getDistance()) # Sort by distance to plane

minDist = la_list[0].getDistance()
maxDist = la_list[len(la_list)-1].getDistance()
distDelta = maxDist - minDist
midDist = minDist + distDelta / 2
print("minDist =", la_list[0].getDistance(), ", maxDist =",maxDist,", midDist =", midDist)
slotWidth = distDelta / 10
slots = [0, 0, 0, 0, 0]
i = 0
while i < len(la_list) and la_list[i].getDistance() - midDist <= -3*slotWidth:
	slots[0] += 1
	i += 1
while i < len(la_list) and la_list[i].getDistance() - midDist <= -1*slotWidth:
	slots[1] += 1
	i += 1
while i < len(la_list) and la_list[i].getDistance() - midDist <= 1*slotWidth:
	slots[2] += 1
	i += 1
while i < len(la_list) and la_list[i].getDistance() - midDist <= 3*slotWidth:
	slots[3] += 1
	i += 1
while i < len(la_list) and la_list[i].getDistance() - midDist > 3*slotWidth:
	slots[4] += 1
	i += 1
print(slots)

## Every local alignment should be accounted for in our slots; verify this
if sum(slots) != len(la_list):
	print("ERROR: sum(slots) =", sum(slots), " but len(la_list) =", len(la_list))

# Create a histogram of the distances to the "perfect local alignment plane"
# Also store them in a file for reference
fOut = open("distances/distances.txt", "w")
distList = list()
for la in la_list:
	fOut.write("d(" + la.qId + "," + la.sId + ") = " + str(la.getDistance()) + "\n") 
	distList.append(la.getDistance())
fOut.close()
plt.hist(distList, bins='auto')
plt.title("Histogram of distance of LAs to plane")
plt.savefig("distances/distances.png")
plt.show()

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
