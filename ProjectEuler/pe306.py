g = [0, 0, 1]
while len(g) <= 524:
	n = len(g)
	s = set()
	for i in range(n-1):
		s.add(g[i]^g[n-2-i])
	v = 0
	while v in s:
		v += 1
	g.append(v)

rep = [4, 5, 5, 9, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4, 8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4]

ans = sum(v != 0 for v in g[1:])
repans = sum(v != 0 for v in rep)

N = int(input())
ans += ((N - (len(g)-1)) // len(rep)) * repans

i, j = (len(g)-1) + ((N - (len(g)-1)) // len(rep)) * len(rep), 0
while i <= N:
	ans += int(rep[j] != 0)
	i += 1
	j = (j + 1) % len(rep)
print(ans)
