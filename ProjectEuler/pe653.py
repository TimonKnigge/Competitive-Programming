L, N, j = map(int, input().split(' '))

r = [6563116]
M = 32745673
for i in range(2, N+1):
	r.append(r[-1]**2 % M)

L -= 20*N

ts, vv = [], 0
for v in r:
	vv = vv + (1 + v % 1000)
	if v <= 10000000:
		ts.append(L-vv)
	else:
		ts.append(L+vv)

ts = list(sorted(ts))
print(ts[j-1] + 10*N)
