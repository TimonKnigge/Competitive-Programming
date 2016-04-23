import sys
ans, cur = (-1.0, ""), ("", -1, 1)
for line in sys.stdin:
	if line[0] == '>':
		if cur[2] > 0 and cur[1] / cur[2] > ans[0]:
			ans = (cur[1] / cur[2], cur[0])
		cur = (line[1:len(line)-1], 0, 0)
	else:
		cur = (cur[0], cur[1] + line.count("G") + line.count("C"),
			cur[2] + len(line) - 1)

if cur[2] > 0 and cur[1] / cur[2] > ans[0]:
	ans = (cur[1] / cur[2], cur[0])
		
print(ans[1])
print(100*ans[0])
