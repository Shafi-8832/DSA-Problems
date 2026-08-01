#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
tree_order_statistics_node_update>;

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
#define int long long

struct EdmondsKarp {
    struct edge {
        int to, cap, rev_idx;
    };
    
    int n;
    vector<vector<edge>> adj;
    vector<pii> parent;

    //
    vector<edge> edges;

    // 1. INIT (incase of multiple test cases)
    void init(int nodes) {
        n = nodes;
        adj.assign(n, vector<edge>());
        parent.assign(n, {-1, -1});
    }

    // 2. The Universal Edge Builder
    void add_edge(int u, int v, int cap) {

        int rev_u = adj[u].size();
        int rev_v = adj[v].size();

        adj[u].pb({v, cap, rev_v});

        adj[v].pb({u, 0, rev_u});
    }

    // 3. The AUGMENTED PATH FINDER
    bool bfs(int s, int t) {
        fill(all(parent), make_pair(-1, -1));
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(s);
        visited[s] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (u == t) return true;
            
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].to;
                if (!visited[v] && adj[u][i].cap > 0) {
                    visited[v] = true;
                    parent[v] = {u, i};
                    q.push(v);
                }
            }
        }
        return false;
    }

    // 3.5 bottleneck finder
    int find_bottleneck(int s, int t) {
        int min_cap = INT64_MAX;

        int cur = t;
        for (; cur != s; ) {
            int from = parent[cur].first; // {from, index in adj[from] }
            int index_in_adjFrom = parent[cur].second;

            edge& edge_in_augmented_path = adj[from][index_in_adjFrom];
            min_cap = min(min_cap, edge_in_augmented_path.cap);

            cur = from;
        }

        return min_cap;
    }

    // 3.6 for unite capcaity the bottleneck is 1...

    // 4. Edmond_Karp
    int get_max_flow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            // general max flow, actual min capacity here.
            int bottleneck = find_bottleneck(s, t);

            // int bottleneck = 1; 
            // For unit-capacity bipartite matching bottleneck is always 1.

            flow += bottleneck;
            // for unite capacity, flow++;
            
            int cur = t;
            while (cur != s) {
                int p = parent[cur].first;
                int idx = parent[cur].second;
                
                edge& forward = adj[p][idx];
                edge& reverse = adj[cur][forward.rev_idx];
                
                forward.cap -= bottleneck;
                reverse.cap += bottleneck;

                // for unit capacity
                // forward.cap ^= 1;
                // reverse.cap ^= 1;
                
                cur = p;
            }
        }
        return flow;
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int M, N; cin >> M >> N;
    // 0 to M-1 --> MEN/WOMEN/Employee
    // M to M+N-1 --> WOMEN/MEN/Job

    int source = M + N;
    int sink = M + N + 1;

    int total_nodes = M + N + 2;

    EdmondsKarp ek;
    ek.init(total_nodes);

    // super source to all of left bipartite set
    for (int i=0; i<M; i++) {
        ek.add_edge(source, i, 1); // or whatever the CAPACITY
    }

    // all of right bipartite set to super sink
    for (int j=M; j<=M+N-1; j++) {
        ek.add_edge(j, sink, 1); // whatever the CAPACITY
    }

    // Middle Edges generation
    for (int i=0; i<=M-1; i++) {
        for (int j=M; j<=M+N-1; j++) {
            if (is_valid_match()) {
                ek.add_edge(i, j, 1); // whatever the CAPACITY
            }
        }
    }

    int max_matches = ek.get_max_flow(source, sink);
    cout << "Maximum Matches : " << max_matches << '\n';


    for (int u=0; u<M; u++) {
        for (int i=0; i<ek.adj[u].size(); i++) {
            int v = ek.adj[u][i].to;
            int remaining_cap = ek.adj[u][i].cap;

            if (v != source && remaining_cap == 0) {
                int woman_index = v - M;
                cout << u << "is married to " << woman_index << '\n';
            }
        }
    }
    
    return 0;
}