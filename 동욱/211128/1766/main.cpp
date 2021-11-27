// 문제집

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int N, M;
    cin >> N >> M;

    vector<int> in_degree(N+1);
    vector<vector<int>> sub_vector(N+1);

    int lhs, rhs;
    for(int i=0; i<M; i++) {
        cin >> lhs >> rhs;

        sub_vector[lhs].push_back(rhs);
        in_degree[rhs]++;
    }
    
    auto cmp_func = [](const auto& lhs, const auto& rhs){
        return lhs > rhs;
    };

    priority_queue<int, vector<int>, decltype(cmp_func)> sub_queue(cmp_func);

    for(int loop=0; loop<N; loop++) {

        for(int i=1; i<=N; i++) {
            if(in_degree[i] == 0) {
                sub_queue.push(i);
                in_degree[i] = -1;
            }
        }


        auto val = sub_queue.top();
        sub_queue.pop();
        cout << val << " ";

        for(auto sub : sub_vector[val]) {
            in_degree[sub]--;
        }

    }
    cout << "\n";

    return 0;
}