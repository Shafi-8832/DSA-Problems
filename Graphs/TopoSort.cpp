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


vector<vector<int>> adj_list;
vector<bool> visited;
vector<bool> pasVisited;
stack<int> topoSort;


bool hasCycle = false;

void dfs(int source) {
    visited[source] = true;
    pasVisited[source] = true;

    for (auto child : adj_list[source]) {
        if (!visited[child]) dfs(child);

        else if (pasVisited[child]) hasCycle = true;
    }

    pasVisited[source] = false;
    topoSort.push(source);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i=0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj_list[a].push_back(b);
    }

    while (!topoSort.empty()) {
        cout << topoSort.top() << " ";
        topoSort.pop();
    }
    
    
    return 0;
}