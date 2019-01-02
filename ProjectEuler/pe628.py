n = int(raw_input())

M = 1008691207
F = [1] * (n+1)
for i in range(1, n+1):
	F[i] = i * F[i-1] % M
PF = [1] * (n+1)
for i in range(1, n+1):
	PF[i] = (PF[i-1] + F[i]) % M

ans = 0
for c in range(n, 0, -1):
	rm = c - 1
	ans = (ans + F[rm]) % M
for r in range(2, n+1, 1):
	rm = r - 1
	ans = (ans + F[rm] + M - PF[rm-1]) % M
print(ans)
print((M + F[n] - ans) % M)
