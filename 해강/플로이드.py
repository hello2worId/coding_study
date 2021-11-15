INF = int(1e9)  # 무한대 -> 10억을 설정

n = int(input())
m = int(input())


graph = [[INF] * (n + 1) for _ in range(n + 1)]

for i in range(m):
    a, b, c = map(int, input().split())
    if graph[a - 1][b - 1] > c:
        graph[a - 1][b - 1] = c
for k in range(n):
    for i in range(n):
        for j in range(n):
            if i != j and graph[i][j] > graph[i][k] + graph[k][j]:
                graph[i][j] = graph[i][k] + graph[k][j]
for i in graph:
    for j in i:
        if j == INF:
            print(0, end=' ')
        else:
            print(j, end=' ')
    print()
