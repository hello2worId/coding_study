// 최종순위

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


int main() {
    int test_case;
    int len;

    cin >> test_case;

    for(int loop=0; loop<test_case; loop++) {
        cin >> len;
        vector<vector<int>> graph(len+1);
        int in_degree[len+1] = {0, };

        vector<int> input_vec(len);

        for(int i=0; i<len; i++) {
            cin >> input_vec[i];
        }
        
        for(int lhs=0; lhs<len-1; lhs++) {
            for(int rhs=lhs+1; rhs<len; rhs++) {
                graph[input_vec[lhs]].push_back(input_vec[rhs]);

            }
        }

        int change_size;
        cin >> change_size;

        for(int i=0; i<change_size; i++) {
            int lhs, rhs;
            cin >> lhs >> rhs;
            
            auto pos = find(graph[rhs].begin(), graph[rhs].end(), lhs);
            if(pos != graph[rhs].end()) {

                graph[rhs].erase(pos);
                graph[lhs].push_back(rhs);
            } else {
                auto pos = find(graph[lhs].begin(), graph[lhs].end(), rhs);
                graph[lhs].erase(pos);
                graph[rhs].push_back(lhs);
            }
        }

        for(int i=0; i<graph.size(); i++) {
            for(int index=0; index<graph[i].size(); index++) {

                in_degree[graph[i][index]]++;
            }
        }

        // 위상정렬
        queue<int> store_degree_zero;
        vector<int> answer;
        bool is_possible = true;
        for(int loop=0; loop<len; loop++) {
            
            for(int i=1; i<len+1; i++) {

                if(in_degree[i] == 0) {

                    store_degree_zero.push(i);
                    in_degree[i] = -1;
                }
            }

            if(store_degree_zero.empty()) {
                is_possible = false;
                break;
            }

            auto node = store_degree_zero.front();
            store_degree_zero.pop();
            answer.push_back(node);

            for(auto res : graph[node]) {
                in_degree[res]--;
            }

        }

        if(is_possible) {
            for(auto res : answer) {
                cout << res << " ";
            }
            cout << "\n";
        }
        else {

            cout << "IMPOSSIBLE\n";
        }




        graph.clear();
    }

    return 0;
}