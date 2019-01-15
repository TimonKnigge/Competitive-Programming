N, M = map(int, input().split(' '))

a = [[0]*(M+1) for _ in range(N+1)]
a[0][0] = 1
for b in range(N+1):
	for w in range(M+1):
		if b == 0 and w == 0: continue
		for x in range(N-b+1):
			for y in range(M-w+1):
				a[x+b][y+w] += a[x][y]
print(a[N][M])
