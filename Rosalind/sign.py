import math, itertools
n = int(input())
print(2**n * math.factorial(n))

def printeach(p, s):
	if len(p) == 0:
		print(s)
	else:
		printeach(p[1:], s + str(p[0]) + " ")
		printeach(p[1:], s + str(-p[0]) + " ")

for p in itertools.permutations(list(range(1, n + 1))):
	printeach(p, "")
