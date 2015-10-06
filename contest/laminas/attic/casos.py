#!/usr/bin/python2
import random

p=random.randint(1,1000)
# s=1000
s=random.randint(101, 1000)
n=random.randint(501, s*5)
iguales=False

if iguales:
    precios=[random.randint(1,2*p)]*n
else:
    precios = [0]*n
    for i in range(n):
            precios[i] = random.randint(1, 3*p)

ultima=random.randint(1,n)
cartas=range(1, ultima)+range(ultima+1, n+1)
meta=5*s-1
crt=n-1
while crt<meta:
	while True:
		a=random.randint(1,n)
		if a!=ultima:
			break
	cartas.append(a)
	crt+=1
random.shuffle(cartas)
cartas.append(ultima)

print n,s,p
for i in range(n-1):
	print precios[i],
print precios[n-1]

for a in range(s):
	crt=5*a
	for i in range(crt,crt+4):
		print cartas[i],
	print cartas[crt+4]
