s, t, i = input(), input(), -1
while True:
	i = str.find(s, t, i + 1)
	if i == -1:
		break
	else:
		print(i + 1, end=" ")
print()
