// 음악프로그램

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main() {

    int N, M;
    cin >> N >> M;
    vector<int> in_degree(N+1);
    vector<vector<int>> sub_vector(N+1);
    queue<int> sub_queue;

    for(int loop=0; loop<M; loop++) {
        int number;
        cin >> number;

        vector<int> singers(number);
        for(int i=0; i<number; i++) {
            cin >> singers[i];
        }
        
        for(int i=0; i<number-1; i++) {
            
            sub_vector[singers[i]].push_back(singers[i+1]);
            in_degree[singers[i+1]]++;
        }
    }

    vector<int> answers(N);
    bool is_answer = true;
    for(int loop=0; loop<N; loop++) {

        for(int i=1; i<=N; i++) {
            if(in_degree[i] == 0) {
                sub_queue.push(i);
                in_degree[i] = -1;
            }
        }

        if(sub_queue.empty()) {
            is_answer = false;
            break;
        }
        
        auto val = sub_queue.front();
        sub_queue.pop();
        answers[loop] = val;

        for(auto sub : sub_vector[val]) {
            in_degree[sub]--;
        }

    }

    if(is_answer) {
        for(auto num : answers) {
            cout << num << "\n";
        }
    } else {
        cout << 0 << "\n";
    }


    return 0;
}