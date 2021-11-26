// 선수과목

#include <iostream>
#include <iostream>
#include <queue>

using namespace std;

int main() {

    int N, M;
    cin >> N >> M;

    vector<vector<int>> subs_vec(N+1);


    for(int i=0; i<M; i++) {

        int lhs, rhs;
        cin >> lhs >> rhs;

        subs_vec[lhs].push_back(rhs);
    }

    vector<int> in_degree(N+1);

    for(int i=0; i<subs_vec.size(); i++) {

        for(auto sub : subs_vec[i]) {
            in_degree[sub]++;
        }
    }

    queue<int> sub_queue;
    int answer[N+1] = {0, };

    // for(int i=1; i<N+1; i++) {
    //     answer[i] = 1;
    // }

    int count = 1;
    bool need_to_up = false;

    for(int i=0; i<N; i++) {
        
        if(need_to_up) {
            count++;
            need_to_up = false;
        }

        for(int index=1; index<=N; index++) {
            if(in_degree[index] == 0) {
                sub_queue.push(index);
                in_degree[index] = -1;
                
                // count++;
                answer[index] = count;
                // answer[index] = i+1;

                need_to_up = true;
            }
        }

        auto res = sub_queue.front();
        sub_queue.pop();

        for(auto sub : subs_vec[res]) {
            in_degree[sub]--;
        }

    }

    for(int i=1; i<=N; i++) {
        cout << answer[i] << " ";
    }
    cout << "\n";

    return 0;
}







