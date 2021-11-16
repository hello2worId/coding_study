# 크루스칼 알고리즘이용
# 같은 집합인지 알아내는 알고리즘
def find(parent,x):
    if parent[x] != x:
        parent[x]  = find(parent,parent[x])
    return parent[x]

def union(parent,a,b):
    a = find(parent,a)
    b = find(parent,b)
    
    if a < b:
        parent[b] = a
    else:
        parent[a] = b

# 노드의 개수 입력받기
n = int(input())
parent = [0] * (n+1)

edges=[]
result =0

for i in range(1,n+1):
    parent[i] = i
    
x = []
y = []
z = []
모든 노드에 대한 좌표 값 입력받기
for i in range(1, n + 1):
    data = list(map(int, input().split()))
    x.append((data[0], i))
    y.append((data[1], i))
    z.append((data[2], i))
    
# 최소거리를 구하기 위해서
x.sort()
y.sort()
z.sort()

# 모든 노드에 대한 좌표 값 입력받기
#min(|xA-xB|, |yA-yB|, |zA-zB|) 이와 같은 조건때문에 x,y,z sort해서 간선정보 구할려고 x,y,z 따로 분리
for i in range(n-1):
    #min_value = min((x[i + 1][0] - x[i][0], x[i][1], x[i + 1][1]),(y[i + 1][0] - y[i][0], y[i][1], y[i + 1][1]),(z[i + 1][0] - z[i][0], z[i][1], z[i + 1][1]))
    #edges.append(min_value)
    edges.append((x[i + 1][0] - x[i][0], x[i][1], x[i + 1][1]))
    edges.append((y[i + 1][0] - y[i][0], y[i][1], y[i + 1][1]))
    edges.append((z[i + 1][0] - z[i][0], z[i][1], z[i + 1][1]))
    
print(edges)
edges.sort()

for edge in edges:
    cost, a, b = edge
    # 사이클이 발생하지 않는 경우에만 집합에 포함
    if find(parent, a) != find(parent, b):
        union(parent, a, b)
        result += cost

print(result)
