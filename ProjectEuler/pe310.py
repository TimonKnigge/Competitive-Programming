N = int(input())
g = [0] * (N+1)
cnt = [0] * 256
xorpair = [0] * 256

ans = 0
for i in range(0, N+1):
	s, j = set(), 1
	while j**2 <= i:
		s.add(g[i - j**2])
		j += 1
	while g[i] in s: g[i] += 1

	# update xor pairs
	cnt[g[i]] += 1
	for j in range(256):
		xorpair[j^g[i]] += cnt[j]

	# Suppose the third stone was an i?
	ans += xorpair[g[i]]

print(ans)
