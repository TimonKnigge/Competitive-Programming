from fractions import *
from decimal import *

g = [None, Fraction(1, 1), Fraction(2, 1)]
for n in range(3, 20):
	g.append(Fraction(2, n-2) * sum(g[i] for i in range(1, n-2+1)))

g2 = g[0:3] + [0 for _ in range(3, 100001)]
for n in range(3, 100001):
	if n % 1000 == 0:
		ans = g2[n-1] * Fraction(1, n)
		print(str.format("{}\t{}", n, float(ans)))
	g2[n] = (Fraction(2, n-2) * g2[n-2] + Fraction((n-3), (n-2)) * g2[n-1])

for n in range(10000, 100000, 10000):
	ans = g2[n-1] * Fraction(1, n)
	print(str.format("{}\t{}\t{}", n, ans, Decimal(ans)))
