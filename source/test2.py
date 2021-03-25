n = int(input())
arr = list(map(int, input().split()))
arr.sort()
for num in arr:
	print(num, end = ' ')
