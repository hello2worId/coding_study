// 줄 세우기

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main() {

    int N, M;
    cin >> N >> M;

    vector<int> in_degree(N+1);
    vector<vector<int>> sub_vector(N+1);

    int lhs, rhs;
    for(int i=0; i<M; i++) {
        cin >> lhs >> rhs;
        sub_vector[lhs].push_back(rhs);

    }
    
    for(int i=1; i<=N; i++) {

        for(auto sub : sub_vector[i]) {
            in_degree[sub]++;
        }
    }
    
    queue<int> sub_queue;
    for(int loop=0; loop<N; loop++) {

        for(int i=1; i<=N; i++) {
            if(in_degree[i] == 0) {
                sub_queue.push(i);
                in_degree[i] = -1;
            }
        }

        auto val = sub_queue.front();
        sub_queue.pop();
        cout << val << " ";

        for(auto sub : sub_vector[val])
            in_degree[sub]--;

    }
    cout << "\n";

    return 0;
}