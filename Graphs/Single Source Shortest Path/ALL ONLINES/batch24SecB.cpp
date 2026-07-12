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

    int n, e, k; cin >> n >> e >> k;
    
    vector<int> d(n + 1, INF);

    vector<vector<pii>> adjList(n + 1, vector<pii>());

    set<pii> pq; // {d value, destination_node}
    
    for (int i=1; i<=k; i++) {
        int x; cin >> x;

        d[x] = 0;
        pq.insert({0, x});
    }


    for (int i=0; i<e; i++) {
        int u, v, w; cin >> u >> v >> w;
        adjList[v].pb({u, w}); // reverse edge
    }
    

    // Shortest Path reconstruct
    vector<int> parent(n + 1, -1);

    
    while (!pq.empty()) {
        auto [dist, u] = *(pq.begin());
        pq.erase(pq.begin());

        for (auto &[w, v] : adjList[u]) {
            if (d[v] > d[u] + w) {
                pq.erase({d[v], v});

                d[v] = d[u] + w;
                parent[v] = u;

                pq.push({d[v], v});
            }
        }
    }

    // vector<int> shortest_path;

    // for (int cur = dest; cur != -1; cur = parent[cur]) {
    //     shortest_path.pb(cur);
    // }
    // reverse(all(shortest_path));

    for (int i=1; i<=n; i++) cout << d[i] << '\n';
    
    return 0;
}