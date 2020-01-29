import random 

plaintext = ''
key = ''

for i in range(128):
	a = random.randint(0,1)
	plaintext += str(a)

for i in range(128):
	a = random.randint(0,1)
	key += str(a)

print plaintext 
print key
