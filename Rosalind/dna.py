def toint(s):
	if s == 'A':
		return 0
	if s == 'C':
		return 1
	if s == 'G':
		return 2
	return 3

res = [0, 0, 0, 0]
for c in input():
	res[toint(c)] += 1
print(res[0], res[1], res[2], res[3])
