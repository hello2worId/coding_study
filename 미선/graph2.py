from collections import deque
# deques는 앞뒤 양쪽 방향에서 엘리먼트 추가 또는 제거할 수 있다.

# 위상 정렬 알고리즘 알아야 한다.
n = int(input())

for i in range(n):
    # 노드의 개수 입력받기
    m = int(input())
    indegree = [0] * (m+1)
    # 각 노드에 연결된 간선 정보를 담기위한 인접 행렬 초기화
    graph = [[False] * (m+1) for i in range(m+1)]
    print(graph)
    #작년 순위 정보 입력
    last_year_rank = list(map(int,input().split()))
    # 방향 그래프의 간선 정보 초기화
    for a in range(m):
        for b in range(a+1,m):
             graph[last_year_rank[a]][last_year_rank[b]] = True
             indegree[last_year_rank[b]] += 1
    print(graph)
    print(indegree)
    # k = int(input())
    # for _ in range(k):
    #     a, b = map(int, input().split())
    
    # 올해 변경된 순위 정보 입력
    k = int(input())
    for i in range(k):
        a, b = map(int, input().split())
        # 간선의 방향 뒤집기 (순위가 바뀌었기 때문에)
        if graph[a][b]:
            graph[a][b] = False
            graph[b][a] = True
            indegree[a] += 1
            indegree[b] -= 1
        else:
            graph[a][b] = True
            graph[b][a] = False
            indegree[a] -= 1
            indegree[b] += 1
            
    # 위상 정렬(Topology Sort) 시작
    result =[]
    q = deque() # 양방향큐를 이용
    
    # 처음 시작할때 진입차수 0인 것을 큐에 삽입
    for i in range(1, n+1):
        if indegree[i]==0:
            q.append(i)
            
    cycle=False # 사이클이 성립될 경우 impossible
    certain=True
    
    for i in range(m):
        # 큐가 비어 있으면 사이클 생성
        if len(q) == 0:
            cycle = True
            break
        if len(q) >=2:
            certain = False
            break
        now = q.popleft()
        result.append(now)
        for j in range(1, m+1):
            if graph[now][j]:
                indegree[j] += -1
                # 새롭게 진입차수가 0이 되는 노드를 큐에 삽입
                if indegree[j] == 0:
                        q.append(j)

    # 사이클이 발생하는 경우(일관성이 없는 경우)
    if cycle:
        print("IMPOSSIBLE")
    # 위상 정렬 결과가 여러 개인 경우
    elif not certain:
        print("?")
    # 위상 정렬을 수행한 결과 출력
    else:
        for i in result:
            print(i, end=' ')
        print()
