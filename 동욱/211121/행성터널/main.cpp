// 행성 터널

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

typedef struct _Pos {
    int x, y, z;
    int index;
} Pos;

int get_min_len(const Pos& lhs, const Pos& rhs) {
    vector<int> res;
    res.push_back(abs(lhs.x - rhs.x)); 
    res.push_back(abs(lhs.y - rhs.y)); 
    res.push_back(abs(lhs.z - rhs.z));

    return *min_element(res.begin(), res.end());
}

int main() {
    int N;
    vector<Pos> loc;
    vector<Edge> edges;

    cin >> N;
    int x, y, z;
    for(int i=0; i<N; i++) {
        Edge::parents.push_back(i);
        
        cin >> x >> y >> z;
        loc.push_back({x, y, z, i});
    }

    sort(loc.begin(), loc.end(), [](const auto& lhs, const auto& rhs){
        return lhs.x < rhs.x;
    });

    for(int i=0; i<loc.size() - 1; i++) {
        edges.push_back(Edge(loc[i].index, loc[i+1].index, loc[i+1].x - loc[i].x));

    }

    sort(loc.begin(), loc.end(), [](const auto& lhs, const auto& rhs){
        return lhs.y < rhs.y;
    });

    for(int i=0; i<loc.size() - 1; i++) {
        edges.push_back(Edge(loc[i].index, loc[i+1].index, loc[i+1].y - loc[i].y));

    }

    sort(loc.begin(), loc.end(), [](const auto& lhs, const auto& rhs){
        return lhs.z < rhs.z;
    });

    for(int i=0; i<loc.size() - 1; i++) {
        edges.push_back(Edge(loc[i].index, loc[i+1].index, loc[i+1].z - loc[i].z));

    }



    // for(int lhs=0; lhs<N; lhs++) {
    //     for(int rhs=lhs+1; rhs<N; rhs++) {
    //         edges.push_back(Edge(lhs, rhs, get_min_len(loc[lhs], loc[rhs])));
    //     }
    // }
    
    sort(edges.begin(), edges.end());

    int sum = 0;
    for(int i=0; i<edges.size(); i++) {

        if(!Edge::is_sibling(edges[i].node[0], edges[i].node[1])) {
            
            sum += edges[i].distance;
            Edge::union_parent(edges[i].node[0], edges[i].node[1]);
        }
    }

    cout << sum << "\n";

    return 0;
}