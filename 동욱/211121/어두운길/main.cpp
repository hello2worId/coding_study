// 어두운 길

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    Edge(int lhs, int rhs, int distance) {
        this->node[0]  = lhs;
        this->node[1]  = rhs;
        this->distance = distance;
    }

    bool operator<(Edge &edge) {
        return this->distance < edge.distance;
    }

    static int get_parent(int child);
    static void union_parent(int lhs, int rhs);
    static bool is_sibling(int lhs, int rhs);

public:    
    int node[2];
    int distance;

    static vector<int> parents;    
};
vector<int> Edge::parents;

int Edge::get_parent(int child) {
    if(parents[child] == child)
        return child;
    
    parents[child] = get_parent(parents[child]);

    return parents[child];
}

void Edge::union_parent(int lhs, int rhs) {
    lhs = get_parent(lhs);
    rhs = get_parent(rhs);

    if(lhs < rhs)
        parents[rhs] = lhs;
    else
        parents[lhs] = rhs;
}

bool Edge::is_sibling(int lhs, int rhs) {

    return get_parent(lhs) == get_parent(rhs);
}

int main() {

    int house_size;
    int load_size;
    vector<Edge> info_vec;

    cin >> house_size >> load_size;

    int total = 0;

    for(int loop=0; loop<load_size; loop++) {
        int lhs, rhs, distance;
        cin >> lhs >> rhs >> distance;

        info_vec.emplace_back(lhs, rhs, distance);
        Edge::parents.push_back(loop);

        total += distance;
    }

    sort(info_vec.begin(), info_vec.end());

    int sum = 0;
    for(int i=0; i<info_vec.size(); i++) {

        if(!Edge::is_sibling(info_vec[i].node[0], info_vec[i].node[1])) {
            
            sum += info_vec[i].distance;
            Edge::union_parent(info_vec[i].node[0], info_vec[i].node[1]);
        }
    }

    cout << total - sum << endl;

    return 0;
}