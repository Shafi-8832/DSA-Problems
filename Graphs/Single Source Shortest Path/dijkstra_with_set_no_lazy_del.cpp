#include<bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define f(t, i, x, y) for (t (i)=(x); (i)<(y); (i)++)
#define fe(t, i, x, y) for (t (i)=(x); (i)<=(y); (i)++)

#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define intmin INT64_MIN
#define INF INT64_MAX
#define int long long


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, e; cin >> n >> e;

    vector<vector<pii>> adjList(n + 1, vector<pii>());

    for (int i=0; i<e; i++) {
        int u, v;
        int w;

        cin >> u >> v >> w;

        // w = 
        adjList[u].pb({w, v});
    }

    vector<int> d(n + 1, INF);

    // Shortest Path reconstruct
    vector<int> parent(n + 1, -1);

    int source; cin >> source;
    d[source] = 0;

    set<pii> pq; // {d value, destination_node}

    pq.insert({d[source], source});
    
    while (!pq.empty()) {
        auto [dist, u] = *(pq.begin());
        pq.erase(pq.begin());

        for (auto &[w, v] : adjList[u]) {
            if (d[u] != INF && d[v] > d[u] + w) {
                pq.erase({d[v], v});

                d[v] = d[u] + w;
                parent[v] = u;

                pq.insert({d[v], v});
            }
        }
    }

    vector<int> shortest_path;
    int dest; cin >> dest;

    for (int cur = dest; cur != -1; cur = parent[cur]) {
        shortest_path.pb(cur);
    }
    reverse(all(shortest_path));

    for (auto& v : shortest_path) {
        cout << v;
        if (v != dest) cout << " -> ";
    }
    
    return 0;
}