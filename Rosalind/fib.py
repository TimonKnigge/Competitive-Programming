n, k = map(int, input().split(" "))
dp = [0, 1]
while len(dp) < n + 1:
	dp.append(dp[-1] + k * dp[-2])
print(dp[-1])
