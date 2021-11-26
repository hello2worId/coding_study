// ACM Craft

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main() {

    // N: 건물 수
    // K: 규칙 수
    int test_case, target, N, K;

    cin >> test_case;
    for(int loop=0; loop<test_case; loop++) {

        cin >> N >> K;
        int build_time[N+1];

        for(int i=1; i<=N; i++)
            cin >> build_time[i];


        // target을 만들기 위해 필요한 건물만 뽑아내기 위한 vector
        vector<vector<int>> needed_vec(N+1);
        // 위상정렬을 위한 vector
        vector<vector<int>> subs_vec(N+1);
        for(int i=0; i<K; i++) {

            int lhs, rhs;
            cin >> lhs >> rhs;

            subs_vec[lhs].push_back(rhs);
            needed_vec[rhs].push_back(lhs);
        }
        cin >> target;

        vector<int> in_degree(N+1);
        for(int i=0; i<subs_vec.size(); i++) {

            for(auto sub : subs_vec[i]) {
                in_degree[sub]++;
            }
        }

        bool checked[N+1] = {false, };
        queue<int> needed_queue;
        needed_queue.push(target);
        
        while(! needed_queue.empty()) {
            auto res = needed_queue.front();
            needed_queue.pop();
            checked[res] = true;

            for(auto need : needed_vec[res])
                needed_queue.push(need);
        }

        // target에 연관되지 않은 건물은 제외
        for(int i=1; i<=N; i++) {

            if(! checked[i])
                in_degree[i] = -1;
        }

        int answer = 0;
        bool is_answer = false;
        queue<int> sub_queue;

        while(true) {

            int max = 0;
            for(int index=1; index<=N; index++) {
                
                if(in_degree[index] == 0) {
                    if(index == target) {
                        is_answer = true;
                        max = build_time[target];

                        break;
                    }

                    sub_queue.push(index);
                    in_degree[index] = -1;

                    if(max < build_time[index]) {
                        max = build_time[index];
                    }
                }
            }
            answer += max;

            if(is_answer) {
                cout << answer << "\n";
                break;
            }

            while(! sub_queue.empty()) {

                auto res = sub_queue.front();
                sub_queue.pop();

                for(auto sub : subs_vec[res])
                    in_degree[sub]--;
            }
        }

    }


    return 0;
}