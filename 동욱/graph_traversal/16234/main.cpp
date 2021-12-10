// 인구 이동

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> population_info;
vector<vector<int>> population_info_changed;
vector<pair<int, int>> move_needed;
vector<vector<bool>> checked;
vector<vector<bool>> checked_bu;
int N, L, R;
bool is_moved;

bool check_condi(int curr_row, int curr_col, int next_row, int next_col);
void bfs(int st_row, int st_col);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> L >> R;
    population_info.resize(N);
    population_info_changed.resize(N);
    checked.resize(N);
    checked_bu.resize(N);

    int number;
    for(int row=0; row<N; row++)
        for(int col=0; col<N; col++) {

            cin >> number;
            population_info[row].push_back(number);
            population_info_changed[row].push_back(number);
            checked[row].push_back(false);
            checked_bu[row].push_back(false);
        }

    int answer = 0;
    while(true) {

        is_moved = false;
        for(int row=0; row<N; row++)
            for(int col=0; col<N; col++) {
                
                if(! checked[row][col]) bfs(row, col);
            }

        if(is_moved) {
            answer++;

            checked = checked_bu;
            population_info = population_info_changed;
        } else {
            break;
        }
    }

    cout << answer << "\n";

    return 0;
}

void bfs(int st_row, int st_col) {

    int drow[4] = {-1, 1, 0, 0}; 
    int dcol[4] = {0, 0, -1, 1}; 

    queue<pair<int,int>> curr_queue;
    curr_queue.push(make_pair(st_row, st_col));
    checked[st_row][st_col] = true;

    while(! curr_queue.empty()) {
        auto curr_node = curr_queue.front();
        curr_queue.pop();

        auto curr_row = curr_node.first;
        auto curr_col = curr_node.second;

        for(int i=0; i<4; i++) {
            auto next_row = curr_row + drow[i];
            auto next_col = curr_col + dcol[i];

            if(check_condi(curr_row, curr_col, next_row, next_col)) {
                curr_queue.push(make_pair(next_row, next_col));
                checked[next_row][next_col] = true;

                move_needed.push_back(make_pair(next_row, next_col));
            }

        }
    }

    if(! move_needed.empty()) {
        move_needed.push_back(make_pair(st_row, st_col));
        int sum = 0;

        for(auto node : move_needed)
            sum += population_info[node.first][node.second];

        auto renew_num = sum / move_needed.size();
        
        for(auto node : move_needed)
            population_info_changed[node.first][node.second] = renew_num;
        
        is_moved = true;
        move_needed.clear();
    }
}

bool check_condi(int curr_row, int curr_col, int next_row, int next_col) {

    if(next_row < 0 || next_row >= N || next_col < 0 || next_col >= N)
        return false;

    if(checked[next_row][next_col] == true)
        return false;

    auto diff = abs(population_info[curr_row][curr_col] - population_info[next_row][next_col]);

    return diff >= L && diff <= R;
}