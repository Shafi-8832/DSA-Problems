#include "bits/stdc++.h"

using namespace std;

#define INF __INT_MAX__

struct Edge {
    int to;
    int weight;
} typedef edge;

class Graph {
    public:
    int V;
    vector<list<edge>> adjList;

    Graph(int V) : V(V) {adjList.resize(V, list<edge>()) }

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
    }
};

void InitializeSingleSource(int V, int s, vector<int>& d, vector<int>& pi){
    for (int i=0; i<V; i++) {
        d[v] = -INF;
        pi[v] = -1;
    }
    d[s] = 0;
}

bool Relax(int u, int v, int w, vector<int>& d, vector<int>& pi) {
    if (d[u] != INF && d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pi[v] = u;
        return true; // v.d was decreased, so need to be pushed in the PQ
    }
    return false; // don't need to push into the PQ
}

void DijkStra(Graph& G, int s) {
    int V = G.V;
    vector<int> d(V, INF);
    vector<int> pi(V, -1);

    InitializeSingleSource(V, s, d, pi);

    vector<int> S;
    set<pair<int, int>> Q;
    Q.push({0, s});


    while (!Q.empty()) {
        int u = Q.front().second;
        Q.pop();

        S.push_back(u);

        for (auto& edge : G.adjList[u]) {
            int v = edge.to;
            int old_dist = d[v];

            if (Relax(u, v, edge.weight, d, pi)) {
                Q.erase({old_dist, v});
                Q.push({d[v], v});
            }
        }
    }

    // print
}

int main() {



    return 0;
}