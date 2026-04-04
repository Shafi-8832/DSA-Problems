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
#define int long long

int hasCycle = 0;

void dfs(int source, vector<bool>& recurStack, vector<bool>& visited, vector<vector<int>>& adj_list) {
    visited[source] = true;
    recurStack[source] = true;

    for (auto child : adj_list[source]) {
        if (!visited[child]) dfs(child, recurStack, visited, adj_list);
        else if (recurStack[child]) {
            cout << "back edge found : " << source << " -> " << child << '\n';
            hasCycle++;
        } 
    }

    recurStack[source] = false;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<vector<int>> adj_list(n + 1, vector<int>());

    for (int i=0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj_list[a].push_back(b); // a --> b
    }

    vector<bool> visited(n + 1, false);
    vector<bool> recurStack(n + 1, false);

    for (int i=1; i<=n; i++) { 
        if (!visited[i]) dfs(i, recurStack, visited, adj_list);
    }

    // you must call dfs from all unvisited nodes to detect
    /* @reason 1 : multiple connected components
       if there are multiple components, then just calling from one component obviously won't work

       @reason 2 : 
       1 --> 2 <-- 3
       if you call dfs from 2 only it will stop immediately

       so, calling dfs from every unvisited node is even more important for directed graphs

       @case
       You skip the loop and only call dfs(start_node) 
       when a problem specifically asks about reachability from a single specific starting point.
    */ 

    cout << "has cycle : " << hasCycle << '\n';


    return 0;
}