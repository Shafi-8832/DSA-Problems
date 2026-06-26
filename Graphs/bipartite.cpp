#include "bits/stdc++.h"

using namespace std;

int main() {
    int n, e; cin >> n >> e;

    vector<vector<int>> adj_list(n);
    bitset<100> visited;
    vector<int> color(n, -1);

    for (int i=0; i<e; i++) {
        int a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    queue<int> q;
    q.push(0);
    visited.set(0, 1);
    color[0] = 0;

    bool biparttite = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj_list[u]) {
            if (!visited[v]) { // IF NOT visited, just color it the oppposite
                visited[v] = 1;
                color[v] = color[u] ^ 1;
                q.push(v);
            }
            else if (color[v] == color[u]) { // IF ALREADY VISITED BEFORE, check the color, if it's different then ok, otherwise NO
                biparttite = false;
            }
        }
    }

    if (biparttite) cout << "bipartite";
    else cout << "not bipartite";

    return 0;
}