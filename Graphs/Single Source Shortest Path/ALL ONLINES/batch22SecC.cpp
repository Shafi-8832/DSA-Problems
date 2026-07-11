#include<bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
#define f(t, i, x, y) for (t (i)=(x); (i)<(y); (i)++)
#define fe(t, i, x, y) for (t (i)=(x); (i)<=(y); (i)++)

#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define intmin INT64_MIN
#define intmax INT64_MAX
#define int long long


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, f; cin >> n >> m >> f;
    vector<int> cap(n + 1);
    for (int i=1; i<=n; i++) cin >> cap[i];

    vector<vector<pii>> adj(n + 1, vector<pii>());
    vector<int> d(n + 1, intmax);

    for (int i=0; i<m; i++) {
        int u, v, w; cin >> u >> v >> w;

        adj[u].pb({w, v});
        adj[v].pb({w, u});
    }
    int k; cin >> k;

    set<pii> pq2; // for greedy distribution of seats
    
    
    set<pii> pq; // {d-value, node}
    d[1] = 0;
    pq.insert({0, 1});
    while (!pq.empty()) {
        int u = pq.begin()->second;
        // after u has been extracted, it's d value has been finalized d[u] = true delta, so it is the perfect time to insert
        pq2.insert({d[u] + f, u});

        pq.erase(pq.begin());

        for (auto& [w, v] : adj[u]) {
            if (d[v] > d[u] + w) {
                pq.erase({d[v], v});
                d[v] = d[u] + w;
                pq.insert({d[v], v});
            }
        }
    }

    vector<int> costs(k, -1);
    int j = 0;
    while (!pq2.empty()) {
        auto [cost, u] = *pq2.begin();
        pq2.erase(pq2.begin());

        int c = cap[u];
        for (int i=0; i<c; i++) {
            if (j >= costs.size()) break;
            costs[j++] = cost;
        }
    }



    
    return 0;
}