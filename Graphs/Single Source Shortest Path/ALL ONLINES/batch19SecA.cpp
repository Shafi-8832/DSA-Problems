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

#define INF 1e18

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector< pair<int, int> >> adj_list(n + 1, vector< pair<int, int> >());
    vector<int> d(n + 1, INF);
    
    
    // Shortest Path Tree reconstruct
    vector<int> parent(n + 1, -1);
    
    
    for (int i=0; i<e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({w, v});
    }
    
    int source; cin >> source;
    
    priority_queue<tiii, vector<tiii>, greater<tiii>()> pq; // {weight, edges, destination} // first minimize total weight, if tie edges
    
    d[source] = 0;

    vector<int> edges(n + 1, INF); // edges[v] = minimum number of edges needed to reach v from source
    edges[source] = 0;
    
    pq.push({0, 0, source});

    while (!pq.empty()) {
        auto [dist, e, u] = pq.front(); // TC O(LogV)
        pq.pop(); // TC O(LogV)

        if ((dist > d[u]) || dist == d[v] && e > edges[u]) continue; // Lazy Deletion

        for (auto& [w, v] : adj_list[u]) { // mathematically provable, EVERY edge is processed exactly once, that's the genius of dijkstra! we never do extra work, we do the least work to get best result
            // this for loop is run SUM(adj_list|u_i|) times which is (directed graphs) E
            if (d[v] > d[u] + w) { // E checks EXACTLY, not less not more, once for EVERY EDGE
                d[v] = d[u] + w;

                edges[v] = edges[u] + 1;

                parent[v] = u; // JUST THIS SINGLE LINE IS ENOUGH FOR PATH RECONSTRUCT

                pq.push({d[v], edges[v], v}); // worst case, pushed all E times = ElogV
            }
            else if (d[v] == d[u] + w) {
                if (edges[v] > edges[u] + 1) edges[v] = edges[u] + 1;
                // or you could write : edges[v] = min(edges[v], edges[u]+1);
                //  d[v] > d[u] + w - very similar
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int u; cin >> u;
        cout << d[u] << '\n';
    }

    int destination;
    cin >> destination;

    vector<int> shortest_path;
    for (int curr = destination; curr != -1; curr = parent[curr]) {
        shortest_path.pb(curr);
    }

    reverse(all(shortest_path));
    

    return 0;
}