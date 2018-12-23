from math import sqrt
# http://laurentmazare.github.io/2014/09/14/counting-coprime-pairs/
def c(N):
  if N < 1:
    return 0
  sqrt_N = int(sqrt(N))
  indexes = [i for i in range(1, 1+sqrt_N)]
  for k in range(sqrt_N, 0, -1):
    if indexes[-1] != N // k: indexes.append(N // k)
  res = {}
  for n in indexes:
    tmp = n ** 2
    if 1 < n:
      sqrt_n = int(sqrt(n))
      for l in range(1, sqrt_n+1):
        tmp -= res[l] * (n // l - n // (l+1))
      for d in range(2, 1 + n // (1 + sqrt_n)):
        tmp -= res[n // d]
    res[n] = tmp
  return (res[N]-1)//2

N = int(input())
M = 1000000007
print(sum(c(N//(2**i)) % M for i in range(1, 50)) % M)
