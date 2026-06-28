// Since Dijkstra processes nodes strictly in order of their shortest distance, 
// the graph of shortest paths is actually a Directed Acyclic Graph (DAG). 
// Because it's a DAG, we can perform standard Dynamic Programming right inside the Dijkstra loop.


#include <bits/stdc++.h> 

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector< pair<int, int> >> adj_list(n + 1, vector< pair<int, int> >());
    vector<int> d(n + 1, -INF);

    for (int i=0; i<e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({w, v});
    }

    vector<int> ways(n + 1, 0);
    vector<int> min_edges(n + 1, -1);
    vector<int> max_edges(n + 1, -1);

    

    return 0;
}