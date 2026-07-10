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

#define INF 1e9

struct Edge {
    int to;
    int time, cost;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int k; cin >> k;
    int n; cin >> n;
    int x; cin >> x;

    vector<vector<Edge>> adj(n + 1, vector<Edge>());

    vector<int> d(n + 1, INF);
    vector<int> parent(n + 1, -1);
    vector<int> time_taken(n + 1, INF); // time_taken to reach city v = time_taken[v]

    for (int i=0; i<x; i++) {
        int u, v, t, c; cin >> u >> v >> t >> c;
        
        // bidirectional routes
        adj[u].pb({v, t, c});
        adj[v].pb({u, t, c});
    }

    int S, D; cin >> S >> D;


    set<pii> pq;
    d[S] = 0;
    time_taken[S] = 0;
    pq.insert({0, S});

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());

        // lazy deletion lagbe na

        for (auto& [v, t, c] : adj[u]) {
            int eff_weight = c + t * k + (u != S) * k;

            if (d[u] != INF && d[v] > d[u] + eff_weight) {
                pq.erase({d[v], v});
                d[v] = d[u] + eff_weight;

                pq.insert({d[v], v});

                parent[v] = u; // parent array has its own Upper Bound property! the pointer onlty gets updated to a strictly better parent!!

                time_taken[v] = time_taken[u] + (t + (u!=S));

                // NOTE : time_taken array has the Upper Bound Property? NO, 
                // path a : cost 5000, time = 4 hours
                // path b : cost 4000, time = 5 hours

                // dijkstra is minimizing cost here! not time! so cost/dist array has the true Upper Bound!!!
                // time array is a slave to dist
                // if time was proportional cost, then it would have the UB property.
            }
        }
    }

    if (d[D] == INF) {
        cout << "ei tuition kora possible nah\n";
        return 0;
    }
    else {
        vector<int> path;
        for (int cur = D; cur != -1; cur = parent[cur]) path.pb(cur);
        reverse(all(path));

        cout << path[0] << "->[";
        for (int i=1; i<path.size()-1;i++) {
            cout << path[i];
            if (i != path.size()-2) cout << "->";
        }
        cout << "]->" << path.back() << " " << time_taken[D] << " " << d[D] << '\n'; 
    }
    
    return 0;
}