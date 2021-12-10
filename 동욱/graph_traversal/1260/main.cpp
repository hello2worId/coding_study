// DFS와 BFS

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// N : 정점의 갯수
// M : 간선의 갯수
int N, M;
int st_node;

vector<vector<int>> link_info;
vector<int> answers;

//DFS
vector<bool> checked_dep;
void dfs(int node) {
    answers.push_back(node);
    checked_dep[node] = true;

    for(auto curr_node : link_info[node]) {

        if(! checked_dep[curr_node]) {
            checked_dep[curr_node] = true;
            dfs(curr_node);
        }
    }

}

//BFS
void bfs() {
    bool checked[N+1] = {false, };
    queue<int> curr_queue;
    curr_queue.push(st_node);
    checked[st_node] = true;
    answers.push_back(st_node);

    while(! curr_queue.empty()) {
        auto curr_node = curr_queue.front();
        curr_queue.pop();

        for(auto node : link_info[curr_node]) {
            if(!checked[node]) {
                curr_queue.push(node);
                checked[node] = true;
                answers.push_back(node);
            }
        }
    }
}


int main() {

    cin >> N >> M >> st_node;
    link_info.resize(N+1);
    checked_dep.resize(N+1, false);

    int lhs, rhs;
    for(int i=0; i<M; i++) {

        cin >> lhs >> rhs;
        link_info[lhs].push_back(rhs);
        link_info[rhs].push_back(lhs);
    }

    for(int i=1; i<=N; i++)
        sort(link_info[i].begin(), link_info[i].end());

    // DFS
    dfs(st_node);
    for(auto node : answers)
        cout << node << " ";
    cout << "\n";
    answers.clear();

    // BFS
    bfs();
    for(auto node : answers)
        cout << node << " ";
    cout << "\n";


    return 0;
}