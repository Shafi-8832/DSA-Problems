#include <bits/stdc++.h>

using namespace std;
#define int long long
#define INF INT64_MAX

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, e;
    cin >> n >> e;

    vector<vector< pair<int, int> >> adj_list(n + 1, vector< pair<int, int> >());
    vector<int> d(n + 1, INF);

    for (int i=0; i<e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({w, v});
    }

    set<pair<int, int>> pq;
    d[1] = 0;
    pq.insert({0, 1});

    while (!pq.empty()) {
        int u = pq.begin()->second;
        int old = pq.begin()->first;
        pq.erase(pq.begin());

        // LAZY deletion
        if (old > d[u]) continue; // {20, 2}, {10, 2}, ignore {20, 2} pop it out

        for (auto& [w, v] : adj_list[u]) { // mathematically provable, EVERY edge is processed exactly once, that's the genius of dijkstra! we never do extra work, we do the least work to get best result
            // this for loop is run SUM(adj_list|u_i|) times which is (directed graphs) E
            if (d[u] != INF && d[v] > d[u] + w) { // E checks EXACTLY, not less not more, once for EVERY EDGE
                d[v] = d[u] + w;
                pq.insert({d[v], v});
            }
        }
    }

    for (int i=1; i<=n; i++) cout << d[i] << " ";

    // LAZY deletion is ABSOLUTELY IMPORTANT
    /*
    When you find a better path to node V, you push {new_distance, V} into the Priority Queue. 
    But the old, worse distance is still sitting in the queue! 
    C++ priority queues do not have an update function.
    When that old, worse version of V eventually rises to the top and pops out, you must ignore it.
    That is exactly what this line does:
    if (d > dist[u]) continue;
    If you forget this line, you process the node anyway and send out a "bad shockwave" of wasted work, leading straight to a Time Limit Exceeded (TLE) verdict.
    */
    return 0;
}
