// 바이러스

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {

    int comp_size;
    int link_size;

    bool link_info[101][101] = {false, };
    bool checked[101] = {false, };

    cin >> comp_size >> link_size;

    int lhs, rhs;
    for(int i=0; i<link_size; i++) {
        cin >> lhs >> rhs;
        link_info[lhs][rhs] = true;
        link_info[rhs][lhs] = true;
    }

    queue<int> curr_queue;
    int answer = 0;

    curr_queue.push(1);
    checked[1] = true;

    while(! curr_queue.empty()) {
        auto curr_node = curr_queue.front();
        curr_queue.pop();

        for(int index=1; index<=100; index++) {
            if(link_info[curr_node][index] && ! checked[index]) {

                curr_queue.push(index);
                checked[index] = true;
                answer++;
            }
        }
    }

    cout << answer << "\n";

    return 0;
}