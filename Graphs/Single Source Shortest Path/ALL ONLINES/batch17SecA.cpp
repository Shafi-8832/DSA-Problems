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
    
    // vector<vector<pair<int, double>>> adjList(n + 1, vector<pair<int, double>>());
    vector<tuple<int, int, double>> edges(e);
    for (int i=0; i<e; i++) {
        int u, v;
        double r;
        cin >> u >> v >> r;
        double weight = -log(r);
        edges[i] = {u, v, weight};
    }

    vector<double> d(n, 0.0);
    vector<double> d_path(n, __DBL_MAX__);
    
    // Shortest Path reconstruct
    vector<int> parent(n, -1);

    int source, dest; cin >> source >> dest;
    d[source] = 0.0

    bool cycle = false;

    for (int i=1; i<=n-1; i++) {
        for (auto& e : edges) {
            int u = get<0>(e);
            int v = get<1>(e);
            double w = get<2>(e);

            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
            }

            if (d_path[u] != __DBL_MAX__ && d_path[v] > d_path[u] + w) {
                d_path[v] = d_path[u] + w;
                parent[v] = u;
            }
        }
    }

        for (auto& e : edges) {
            int u = get<0>(e);
            int v = get<1>(e);
            double w = get<2>(e);

            if (d[v] > d[u] + w) {
                cycle = true;
                break;
            }
        }

    if (cycle) {
        cout << "There is an anomaly";
        return 0;
    }

    if (d_path[dest] == __DBL_MAX__) {
        cout << "No anomaly but destination is unreachable";
    }

    cout << "Best Exchange rate : ";

    cout << exp(-d_path[dest]);

    vector<int> shortest_path;

    for (int cur = dest; cur != -1; cur = parent[cur]) {
        shortest_path.pb(cur);
    }
    reverse(all(shortest_path));

    for (auto& v : shortest_path) cout << v << "->";
    
    return 0;
}