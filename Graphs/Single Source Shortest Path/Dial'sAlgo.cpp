#include "bits/stdc++.h"

using namespace std;

#define INF 1e18

int main() {
    int n, e, k;
    cin >> n >> e >> k;

    vector<vector< pair<int, int> >> adj_list(n + 1, vector< pair<int, int> >());
    vector<int> d(n + 1, -INF);

    for (int i=0; i<e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({w, v});
    }

    int source; cin >> source;

    vector<queue<int>> bucket(k + 1); // BFS/Djikstra queue
    d[source] = 0;
    bucket[0].push(source);

    int active_elements = 1; // this just means that the modified Queue is not empty, that is, the algo is not completely done.

    // NOTE : Dijkstra doesn't sort by single edges; it sorts by the total distance from the start (d[v]). ****

    int current_dist = 0; // sparse graph hoile ei dist barte barte onk hoye jaite pare
    while (active_elements > 0) {
        
        while (bucket[current_dist % (k+1)].empty()) current_dist++;


        int u = bucket[current_dist % (k + 1)].front();

        bucket[current_dist % (k + 1)].pop(), active_elements--;

        for (auto& [w, v] : adj_list[u]) {

            if (d[v] > current_dist + w) {
                d[v] = current_dist + w;
                bucket[d[v] % (k + 1)].push(v);
                active_elements++;
            }
        }
    }



    int q; cin >> q;
    while (q--) {
        int u; cin >> u;
        cout << d[u] << '\n';
    }


    return 0;
}