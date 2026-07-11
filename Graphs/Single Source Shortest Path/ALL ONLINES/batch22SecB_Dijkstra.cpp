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

    int n, m, k, b, e; cin >> n >> m >> k >> b >> e;

    vector<int> d(n + 1, intmax);
    vector<vector<pii>> adj(n + 1, vector<pii>());
    set<pii> pq;
    
    for (int i=0; i<k; i++) {
        int cap; cin >> cap;
        d[cap] = 0;
        pq.insert({0, cap});
    }

    vector<bool> blocked(n + 1, false);
    // bitset<MAX_NODES>block(n+1, false);
    for (int i=0; i<b; i++) {int bl; cin >> bl; blocked[bl] = true;}
    

    vector<int> destinations;
    for (int i=0; i<e; i++) {
        int emer; cin >> emer;
        destinations.pb(emer);
    }

     // edges(m) leikha abar push_back korte gesi common mistake
    for (int i=0; i<m; i++) {
        int u, v, w; cin >> u >> v >> w;
        if (blocked[u] || blocked[v]) continue;
        
        adj[u].pb({w, v});
    }

    
    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());

        for (auto& [w, v] : adj[u]) {
            if (d[v] > d[u] + w) {
                pq.erase({d[v], v});
                d[v] = d[u] + w;
                pq.insert({d[v], v});
            }
        }
    }



        for (auto& dest : destinations) {
            cout << dest << "->";
            if (d[dest] == intmax) cout << "INF";
            else cout << d[dest];
            cout << '\n';
        }
    

    
    return 0;
}