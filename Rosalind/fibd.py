n, m = map(int, input().split(" "))
dp1, dp2 = [1], [1]
while len(dp1) < n:
	val1 = dp1[-1]
	if len(dp1) >= m:
		val1 -= dp2[-m]
	val2 = 0 if len(dp1) < 2 else dp1[-2]
	if len(dp1) >  m:
		val2 -= dp2[-m-1]
	dp1.append(val1 + val2)
	dp2.append(val2)
print(dp1[-1])
