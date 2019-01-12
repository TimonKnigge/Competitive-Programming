def mpw(a, b, m):
	if b == 0: return 1
	r = mpw(a*a%m, b//2, m)
	if b%2:
		r = r*a%m
	return r

M = 10**16

m = [int(i == 0) for i in range(250)]
for i in range(1, 250250+1):
	s = mpw(i, i, 250)
	mm = [0]*250
	for i, v in enumerate(m):
		mm[i] = (mm[i] + v) % M
		mm[(i+s)%250] = (mm[(i+s)%250] + v) % M
	m = mm

print((M+m[0]-1)%M)
