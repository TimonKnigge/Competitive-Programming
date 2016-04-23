import sys, math
A, C = 0, 0
for line in sys.stdin:
	if line[0] == '>':
		continue
	A += line.count("A")
	C += line.count("C")
print(math.factorial(A) * math.factorial(C))
