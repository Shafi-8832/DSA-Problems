#include<bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using tiii = tuple<int, int, int>;
using pll = pair<ll, ll>;
#define f(t, i, x, y) for (t (i)=(x); (i)<(y); (i)++)
#define fe(t, i, x, y) for (t (i)=(x); (i)<=(y); (i)++)

#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define intmin INT64_MIN
#define int long long



int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    

    int n, m;
    cin >> n >> m;
    vector<vector<pii>> adj(n, vector<pii>());
    for (int i=0; i<m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({w, v});
        adj[v].pb({w, u});
    }

    priority_queue<tiii, vector<tiii>, greater<tiii>()> pq; // {weight, origin, destination}

    vector<bool> in_mst(n, false); // or you can say, in S, in CUT // the growing Empire
    set<pii> final_edges;


    int mst = 0;
    int edges_taken = 0;
    int nodes_taken = 0;

    pq.push({0, -1, 0}); // virtual node -1 to node 0

    bool possible = false;

    while (!pq.empty()) {
        int w = get<0>(pq.top());
        int u = get<1>(pq.top()); // origin
        int v = get<2>(pq.top()); // destination --> extracted ----> into the S set

        pq.pop(); // extraction

        
        if (in_mst[v]) continue; // then some other edge to this node V has been picked up earlier, so you can't take this, otherwise it owuld create a cycle        
        // WHY : (LAZY DELETION)
        // the reason : The Safety Net (if (in_mst[v]) continue;): Why do we still need this if the first one prevents cycles? Because of timing.
        // When an edge is pushed into the queue, its destination node might not be in the MST yet. 
        // It was a perfectly valid, non-cycle-creating move at the time. 
        // But while it was sitting in the queue waiting its turn, 
        // some other cheaper edge grabbed that destination node first. 
        // When our waiting edge finally gets extracted, 
        // taking it would now create a cycle. The safety net catches these delayed cycles and throws them out.
        
        
        // Conquer the city!
        in_mst[v] = true;
        mst += w;
        nodes_taken++; // upon extraction, the destination node v has been engulfed into the set S
        final_edges.insert({u, v}); // Only add final edges, upon extraction, because, the heap extracts the cheapest CROSS EDGE


        
        if (nodes_taken == n || edges_taken == n - 1) {
            possible = true;
            break;
        }

        for (auto [w2, v2] : adj[v]) {
            if (in_mst[v2]) continue; // OBVIOUS CYCLE!!!! IGNORE!
            
            pq.push({w2, v, v2});
        }
    }

    final_edges.erase({-1, 0});

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    cout << mst << '\n';
    for (auto& e : final_edges) {
        cout << e.first << " " << e.second << '\n';
    }

    return 0;
}