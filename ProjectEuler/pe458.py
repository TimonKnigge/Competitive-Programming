M = 10**9

def mm(l, r):
	n = len(l)
	return [[sum(l[a][b]*r[b][c] for b in range(n))%M for c in range(n)] for a in range(n)]

def mpw(a, b):
	n = len(a)
	if b == 0: return [[int(i == j) for i in range(n)] for j in range(n)]
	c = mpw(mm(a, a), b//2)
	if b%2 == 1:
		c = mm(c, a)
	return c

mat = [
	[1,6,0,0,0,0],
	[1,1,5,0,0,0],
	[1,1,1,4,0,0],
	[1,1,1,1,3,0],
	[1,1,1,1,1,2],
	[1,1,1,1,1,1]
]

N = int(input())
mat = mpw(mat, N-1)
print(str.format("answer for {} is {}", N, sum(7*mat[0][i] for i in range(6))%M))
