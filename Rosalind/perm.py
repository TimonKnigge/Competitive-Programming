import math, itertools
n = int(input())
print(math.factorial(n))
for p in itertools.permutations(list(range(1, n + 1))):
	for numb in p:
		print(numb, end=" ")
	print()
