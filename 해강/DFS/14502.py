import copy
from itertools import combinations

n, m = map(int, input().split())

# graph 생성
graph = []
for i in range(n):
    graph.append(list(map(int, input().split())))

# 이동 방향
dx = [-1, 1, 0, 0]
dy = [0, 0, 1, -1]


# dfs 구현
def dfs(x, y):
    graph_[x][y] = 2

    for step in range(4):
        nx = x + dx[step]
        ny = y + dy[step]

        if nx <= -1 or nx >= n or ny <= -1 or ny >= m:
            continue
        if graph_[nx][ny] != 0:
            continue
        else:
            dfs(nx, ny)


# virus, zeros 위치 저장
virus = []
zeros = []
for i in range(n):
    for j in range(m):
        if graph[i][j] == 2:
            virus.append([i, j])
        elif graph[i][j] == 0:
            zeros.append([i, j])

# 3개의 벽이 세워질 수 있는 경우의 수
zeros_combi = combinations(zeros, 3)

# 3개의 벽이 세워질 수 있는 경우의 수 마다 안전한 지역을 safety_zone_list에 저장
# for문이 끝나면 max(safety_zone_list) 통해 값 return
safety_zone_list = []
for combi in zeros_combi:
    graph_ = copy.deepcopy(graph)

    graph_[combi[0][0]][combi[0][1]] = 1
    graph_[combi[1][0]][combi[1][1]] = 1
    graph_[combi[2][0]][combi[2][1]] = 1

    for vi in virus:
        dfs(vi[0], vi[1])

    safety_zone = 0
    for row in range(n):
        for col in range(m):
            if graph_[row][col] == 0:
                safety_zone += 1

    safety_zone_list.append(safety_zone)

print(max(safety_zone_list))
