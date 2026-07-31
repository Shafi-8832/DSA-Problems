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


int bfs(int source, int dest, vector<int>& parent, vector<vector<int>>& curr_cap, vector<vector<int>>& adj_list) {
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
        
        for (auto v : adj_list[u]) {
            if (!visited[v] && curr_cap[u][v] > 0) {
                visited[v] = true;

                min_cap[v] = min(min_cap[u], curr_cap[u][v]);
                parent[v] = u;
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

    vector<vector<int>> curr_cap(n, vector<int>(n, 0));
    vector<vector<int>> flow(n, vector<int>(n, 0)); // f(u, v) = 0 if (u, v) doesn't exist
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> adj_list(n, vector<int>());
    vector<int> parent(n, -1);


    for (int i=0; i<e; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        capacity[a][b] = c;

        curr_cap[a][b] += c;


        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    int source, dest; cin >> source >> dest;

    int bottleneck = 0;
    int max_flow = 0;

    while (( bottleneck = bfs(source, dest, parent, curr_cap, adj_list) ) != -1) {
        max_flow += bottleneck; // corollary 26.3

        // trace the augmented path
        int cur = dest;
        while (parent[cur] != -1) {
            // edge : (parent[cur], cur)
            int from = parent[cur];
            int to = cur;
            // if edge in E
            if (capacity[from][to] > 0) { // equivalent to checking : if (u, v) in E IN CORMEN
                flow[from][to] += bottleneck;
            }
            else {
                flow[to][from] -= bottleneck;
            }

            // augmented path STRICTLY decreases the flow of forward edge, and STRICTLY increases the flow of reverse edge
            curr_cap[from][to] -= bottleneck;
            curr_cap[to][from] += bottleneck;

            cur = parent[cur];
        }

        fill(all(parent), -1);
    }

    cout << max_flow << "\n";

    // final flow of the edges
    for (int u=0; u<n; u++) {
        for (int v : adj_list[u]) {
            if (capacity[u][v] == 0) continue;
            cout << "(" << u << ", " << v << ") : ";
            cout << capacity[u][v] - curr_cap[u][v] << "/" << capacity[u][v];
        }
    }


    return 0;
}