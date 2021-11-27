// 선수과목

#include <iostream>
#include <iostream>
#include <queue>

using namespace std;

int main() {

    int N, M;
    cin >> N >> M;

    vector<vector<int>> subs_vector(N+1);
    vector<int> in_degree(N+1);
    queue<int> sub_queue;


    int lhs, rhs;
    for(int i=0; i<M; i++) {

        cin >> lhs >> rhs;

        subs_vector[lhs].push_back(rhs);
        in_degree[rhs]++;
    }

    vector<int> answer(N+1);

    for(int i=0; i<N; i++) {
        for(int index=1; index<=N; index++) {
            if(in_degree[index] == 0) {
                sub_queue.push(index);
                in_degree[index] = -1;
                
                answer[index] = i+1;
            }
        }

        while(! sub_queue.empty()) {

            auto res = sub_queue.front();
            sub_queue.pop();

            for(auto sub : subs_vector[res]) {
                if(in_degree[sub] > 0)
                    in_degree[sub]--;
            }
        }

    }

    for(int i=1; i<=N; i++) {
        cout << answer[i] << " ";
    }
    cout << "\n";

    return 0;
}







