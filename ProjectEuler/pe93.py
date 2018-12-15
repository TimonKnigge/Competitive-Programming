from fractions import Fraction

sign = lambda x: 1 if x > 0 else (-1 if x < 0 else 0)

def rec(l, s):
	if len(l) == 1:
		s.add(l[0])
		return
	for i in range(len(l)):
		for j in range(i):
			nl = l[:j] + l[j+1:i] + l[i+1:]
			rec(nl + [l[i]+l[j]], s)
			rec(nl + [l[i]-l[j]], s)
			rec(nl + [l[j]-l[i]], s)
			rec(nl + [l[i]*l[j]], s)
			if l[i] != 0:
				rec(nl + [sign(l[i]) * sign(l[j]) * abs(l[j]) / abs(l[i])], s)
			if l[j] != 0:
				rec(nl + [sign(l[i]) * sign(l[j]) * abs(l[i]) / abs(l[j])], s)

def test(a,b,c,d):
	s = set()
	rec([Fraction(a), Fraction(b), Fraction(c), Fraction(d)], s)
	i = 1
	while True:
		if Fraction(i) not in s:
			return i-1
		i += 1

best = 0
for a in range(0, 10):
	for b in range(a+1, 10):
		for c in range(b+1, 10):
			for d in range(c+1, 10):
				m = test(a, b, c, d)
				if best < m:
					best = m
					print(str.format("new best {} with {} {} {} {}", best, a, b, c, d))
