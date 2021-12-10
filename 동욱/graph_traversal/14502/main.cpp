// 연구소

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int virus_size;
// 위치 정보
vector<pair<int,int>> virus_pos;
vector<pair<int,int>> room_pos;
vector<pair<int,int>> wall_pos;

// 연구소 맵
vector<vector<int>> lab_info;

// 가상벽이 세워진 경우의 맵
vector<vector<int>> lab_info_added;


void bfs();

int main() {

    cin >> N >> M;
    lab_info.resize(N);
    lab_info_added.resize(N);

    virus_size = N * M;

    int info;
    for(int row=0; row<N; row++) {
        for(int col=0; col<M; col++) {
            cin >> info;
            lab_info[row].push_back(info);

            if(info == 0) room_pos.push_back(make_pair(row, col));
            else if(info == 1) wall_pos.push_back(make_pair(row, col));
            else if(info == 2) virus_pos.push_back(make_pair(row, col));
        }
    }

    for(int i=0; i<room_pos.size()-2; i++)
        for(int j=i+1; j<room_pos.size()-1; j++)
            for(int k=j+1; k<room_pos.size(); k++) {
                lab_info_added = lab_info;

                lab_info_added[room_pos[i].first][room_pos[i].second] = 1;
                lab_info_added[room_pos[j].first][room_pos[j].second] = 1;
                lab_info_added[room_pos[k].first][room_pos[k].second] = 1;

                // BFS
                bfs();
            }



    cout << N*M - (wall_pos.size() + 3) - virus_size << "\n";


    return 0;
}


int drow[4] = {-1, 1, 0, 0};
int dcol[4] = {0, 0, -1, 1};

bool check_boundary(int row, int col) {

    return row >= 0 && row < N && col >= 0 && col < M;
}

void bfs() {
    queue<pair<int,int>> curr_queue;

    int count = 0;
    for(auto node : virus_pos) {
        
        curr_queue.push(node);
        count++;
    }

    while(! curr_queue.empty()) {

        auto curr_node = curr_queue.front();
        curr_queue.pop();

        auto curr_row = curr_node.first;
        auto curr_col = curr_node.second;

        for(int i=0; i<4; i++) {

            auto next_row = curr_row+drow[i];
            auto next_col = curr_col+dcol[i];

            if(check_boundary(next_row, next_col)
            && lab_info_added[next_row][next_col] == 0) {

                lab_info_added[next_row][next_col] = 2;
                curr_queue.push(make_pair(next_row, next_col));
                count++;
            }
        }
    }

    if(count < virus_size)
        virus_size = count;
}



