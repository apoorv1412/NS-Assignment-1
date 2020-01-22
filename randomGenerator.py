import sys
sys.stdout = open('plaintext.txt', 'w')

import random
s = ''
size = 128
for i in range(size):
	bit = random.randint(0,1)
	s += str(bit)
print s