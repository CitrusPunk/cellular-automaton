#rule30
from pref import *

def getNextGen(old = []):
	nextGen = old[:]
	
	#left border
	num = 0
	if(old[0] == 1): num += 2
	if(old[1] == 1): num += 1
	nextGen[0] = rule[num]

	#"body"-field
	for i in range(1,len(old)-1):
		num = 0	
		if(old[i-1] == 1): num += 4
		if(old[i] == 1): num += 2
		if(old[i+1] == 1): num += 1
		nextGen[i] = rule[num]

	#right border
	num = 0
	if(old[len(old)-2] == 1): num += 4
	if(old[len(old)-1] == 1): num += 2
	nextGen[len(old)-1] = rule[num]

	return nextGen

if (__name__ == "__main__"):
	
	while True:
		print ''.join(mapping[s] for s in start)
		raw_input()
		new = getNextGen(start)
		start = new
