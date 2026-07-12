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

    vector<vector<pair<int, double>>> adjList(n, vector<pair<int, double>>());
    for (int i=0; i<e; i++) {
        int u, v;
        double r;
        cin >> u >> v >> r;
        double w = -log(r);
        adjList[u].pb({w, v});
    }

    vector<double> d(n, 1e9);

    // Shortest Path reconstruct
    vector<int> parent(n, -1);

    int source, dest; cin >> source >> dest;
    d[source] = 0;

    set<pair<double, int>> pq; // {d value, destination_node}

    pq.insert({0.0, source});
    
    while (!pq.empty()) {
        auto [dist, u] = *(pq.begin());
        pq.erase(pq.begin());

        for (auto &[w, v] : adjList[u]) {
            if (d[v] > d[u] + w) {
                pq.erase({d[v], v});

                d[v] = d[u] + w;
                parent[v] = u;

                pq.insert({d[v], v});
            }
        }
    }
    cout << "Most reliable path score : " << exp(-d[dest]);

    vector<int> shortest_path;

    for (int cur = dest; cur != -1; cur = parent[cur]) {
        shortest_path.pb(cur);
    }
    reverse(all(shortest_path));

    for (auto u : shortest_path) {
        cout << u;
        if (u != dest) cout << " -> ";
    }
    
    return 0;
}