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


struct EdmondsKarp {
    struct edge {
        int to;
        long long cap;
        int rev_idx;
        bool is_real; // Crucial for path extraction and finding Min-Cut edges
    };
    
    int n;
    vector<vector<edge>> adj;
    vector<pair<int, int>> parent;

    // 1. INITIALIZATION (Always call this first in every test case)
    void init(int nodes) {
        n = nodes;
        adj.assign(n, vector<edge>());
        parent.assign(n, {-1, -1});
    }

    // 2. EDGE BUILDER
    void add_edge(int u, int v, long long cap) {
        int rev_u = adj[u].size();
        int rev_v = adj[v].size();

        // Forward edge (is_real = true)
        adj[u].push_back({v, cap, rev_v, true});
        // Phantom reverse edge for "undo" (is_real = false, starts with 0 cap)
        adj[v].push_back({u, 0, rev_u, false});
    }

    // 3. AUGMENTING PATH FINDER
    bool bfs(int s, int t) {
        fill(parent.begin(), parent.end(), make_pair(-1, -1));
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
                // Walk down ANY pipe (real or phantom) that has capacity > 0
                if (!visited[v] && adj[u][i].cap > 0) {
                    visited[v] = true;
                    parent[v] = {u, i};
                    q.push(v);
                }
            }
        }
        return false;
    }

    long long find_bottleneck(int s, int t) {
        long long min_cap = 2e18; // Infinity
        int cur = t;
        while (cur != s) {
            int from = parent[cur].first;
            int idx = parent[cur].second;
            min_cap = min(min_cap, adj[from][idx].cap);
            cur = from;
        }
        return min_cap;
    }

    // 4. THE MAIN ENGINE (Calculates Max Flow)
    // Tip: If you add new edges later, just call this AGAIN without resetting!
    long long get_max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            long long bottleneck = find_bottleneck(s, t);
            flow += bottleneck;
            
            int cur = t;
            while (cur != s) {
                int p = parent[cur].first;
                int idx = parent[cur].second;
                
                edge& forward = adj[p][idx];
                edge& reverse = adj[cur][forward.rev_idx];
                
                forward.cap -= bottleneck;
                reverse.cap += bottleneck;
                
                cur = p;
            }
        }
        return flow;
    }

    // =================================================================
    // PATTERN 4 TOOLS: MIN-CUT & RESIDUAL GRAPH ANALYSIS
    // =================================================================

    // Finds SET S: Nodes reachable from the Source in the residual graph.
    vector<bool> get_reachable(int start_node) {
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(start_node);
        visited[start_node] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto& edge : adj[u]) {
                // DO NOT check is_real here! We must allow phantom undo pipes.
                if (!visited[edge.to] && edge.cap > 0) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        return visited;
    }

    // Finds nodes that can drain to the Sink in the residual graph.
    vector<bool> get_reachable_reverse(int target_node) {
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(target_node);
        visited[target_node] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto& edge : adj[u]) {
                int v = edge.to;
                edge& reverse_pipe = adj[v][edge.rev_idx];
                
                if (!visited[v] && reverse_pipe.cap > 0) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return visited;
    }
};




// [PASTE THE EDMONDS-KARP STRUCT HERE]

void solve(int tc) {
    int N, M; // N = Number of nodes/items, M = Number of edges/rules
    cin >> N >> M;

    // 1. DEFINE YOUR ID SPACE
    // If using 1-based indexing for N cities, you need (N + 1) slots.
    // If you need a Super Source and Super Sink, you might need (N + 3) slots.
    int total_nodes = N + 1; 
    
    EdmondsKarp ek;
    ek.init(total_nodes); // Always initialize first to clear the graph!

    // 2. DEFINE SOURCE AND SINK
    int source = 1;
    int sink = N;

    // 3. PARSE THE EDGES
    for (int i = 0; i < M; i++) {
        int u, v;
        long long cap;
        cin >> u >> v >> cap;
        
        // Add the directed edge
        ek.add_edge(u, v, cap);
        
        /* 
        ⚠️ CP GOTCHA: UNDIRECTED GRAPHS ⚠️
        If the problem says "roads are two-way", you MUST add a second 
        edge going the opposite direction with the same capacity!
        
        ek.add_edge(v, u, cap); 
        */
    }

    // (Optional) Add your Super Source / Super Sink edges here if doing Bipartite Matching

    // 4. EXECUTE THE BLACK BOX
    long long max_flow = ek.get_max_flow(source, sink);

    // 5. OUTPUT THE ANSWER
    // Formatting standard for LightOJ, Codeforces, etc.
    cout << "Case " << tc << ": " << max_flow << "\n";

    // 6. THE AFTERMATH (Paste whatever pattern you need here)
    // e.g., finding the Min-Cut, printing paths, etc.
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    

    int T = 1;
        // Comment out the next line if the problem only has ONE test case and no 'T'
        cin >> T; 
        
        for (int tc = 1; tc <= T; tc++) {
            solve(tc);
        }

    // who matched whom

    // Look at left-side entities
    for (int u = 0; u < LeftSetSize; u++) {
        for (auto& edge : ek.adj[u]) {
            // If it's a real edge, not pointing to Source/Sink, and fully used up
            if (edge.is_real && edge.to != source && edge.to != sink && edge.cap == 0) {
                cout << "Node " << u << " paired with Node " << edge.to << "\n";
            }
        }
    }


    // Trace routes from Source to Sink
    for (int i = 0; i < max_routes; i++) {
        int curr = source;
        while (curr != sink) {
            for (auto& edge : ek.adj[curr]) {
                if (edge.is_real && edge.cap == 0) {
                    cout << edge.to << " ";
                    edge.cap = -1; // Destroy evidence so next route doesn't use it
                    curr = edge.to;
                    break;
                }
            }
        }
    }

    vector<bool> in_set_S = ek.get_reachable(source);

    for (int u = 0; u < total_nodes; u++) {
        // Only check nodes inside the reachable traffic jam (Set S)
        if (in_set_S[u]) {
            for (auto& edge : ek.adj[u]) {
                // A real road that crosses the border into Set T
                if (edge.is_real && !in_set_S[edge.to]) {
                    cout << "Min-Cut Road: " << u << " -> " << edge.to << "\n";
                }
            }
        }
    }


    vector<bool> in_set_S = ek.get_reachable(source);
    vector<bool> can_reach_Sink = ek.get_reachable_reverse(sink);

    // For a proposed new road from U to V:
    if (in_set_S[u] && can_reach_Sink[v]) {
        cout << "Building this will increase Max Flow!\n";
    }

    return 0;
}