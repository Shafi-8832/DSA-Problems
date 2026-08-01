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

typedef struct Edge {
    int to;
    int capacity;
    int flow;
    int rev_index;
} Edge;


int bfs(int source, int dest, vector<pii>& parent, vector<vector<Edge>>& adj_list) {
    int n = parent.size();

    queue<int>q;
    q.push(source);

    vector<bool> visited(n, false);
    visited[source] = true;
    vector<int> min_cap(n);
    min_cap[source] = __INT_MAX__; // infinte water glitch

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == dest) return min_cap[u];
        
        for (int i=0; i<adj_list.size(); i++) {
            auto& edge = adj_list[u][i];
            int v = edge.to;
            if (!visited[v] && edge.capacity - edge.flow > 0) {
                visited[v] = true;

                min_cap[v] = min(min_cap[u], edge.capacity - edge.flow);
                parent[v] = {u, i}; // so that I can directly jump to that specific edge later
                q.push(v);
            }
        }
    }

    return -1;
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    
    int n, e; cin >> n >> e;

    // vector<vector<int>> curr_cap(n, vector<int>(n, 0));
    // // vector<vector<int>> flow(n, vector<int>(n, 0)); // f(u, v) = 0 if (u, v) doesn't exist
    // vector<vector<int>> capacity(n, vector<int>(n, 0));

    vector<vector<Edge>> adj_list(n, vector<Edge>());
    vector<pii> parent(n, {-1, -1});


    for (int i=0; i<e; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        int rev_a = adj_list[b].size();
        int rev_b = adj_list[a].size();

        adj_list[a].pb({b, c, 0, rev_a});
        adj_list[b].pb({a, 0, 0, rev_b});
    }

    int source = 0, dest = n-1;

    int bottleneck = 0;
    int max_flow = 0;

    while (( bottleneck = bfs(source, dest, parent, adj_list) ) != -1) {
        max_flow += bottleneck; // corollary 26.3

        // trace the augmented path
        int cur = dest;
        while (parent[cur].first != -1) {

            int from = parent[cur].first;
            int edge_index = parent[cur].second;

            auto& forward = adj_list[from][edge_index];
            auto& reverse = adj_list[cur][forward.rev_index];

            // augmented path STRICTLY decreases the flow of forward edge, and STRICTLY increases the flow of reverse edge
            forward.flow += bottleneck;
            reverse.flow -= bottleneck;

            cur = from;
        }

        fill(all(parent), make_pair(-1, -1));
    }

    cout << max_flow << "\n";

    // final flow of the edges
    // for (int u=0; u<n; u++) {
    //     for (auto& edge : adj_list[u]) {
    //         if (edge.capacity == 0) continue;

    //         int v = edge.to;
    //         cout << "(" << u << ", " << v << ") : ";
    //         cout << edge.flow << "/" << edge.capacity << '\n';
    //     }
    // }


    return 0;
}