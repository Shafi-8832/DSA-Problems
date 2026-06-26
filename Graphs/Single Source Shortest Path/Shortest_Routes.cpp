#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector< pair<int, int> >> adj_list(n + 1, vector< pair<int, int> >());
    vector<int> d(n + 1, INF);

    for (int i=0; i<e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({w, v});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        int u = pq.top().second; // TC O(LogV)
        pq.pop(); // TC O(LogV)

        for (auto& [w, v] : adj_list[u]) { // mathematically provable, EVERY edge is processed exactly once, that's the genius of dijkstra! we never do extra work, we do the least work to get best result
            // this for loop is run SUM(adj_list|u_i|) times which is (directed graphs) E
            if (d[u] != INF && d[v] > d[u] + w) { // E checks EXACTLY, not less not more, once for EVERY EDGE
                d[v] = d[u] + w;
                pq.push({d[v], v}); // worst case, pushed all E times = ElogV
            }
        }
    }

    for (int i=1; i<=n; i++) cout << d[i] << " ";


    return 0;
}
