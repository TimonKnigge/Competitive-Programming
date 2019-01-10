from itertools import product
n, MOD, B = int(input()), 1234567890, 50
d = [0] * B
for i in range(B-1, -1, -1): d[i] = (n>>i) - sum(d[i+1:])
print(sum(d[a]*d[b]*d[c]*int((a^b^c)>0) for a,b,c in product(range(B), repeat=3)) % MOD)
