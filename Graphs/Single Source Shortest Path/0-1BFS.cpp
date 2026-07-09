#include "bits/stdc++.h"

using namespace std;

#define INF 1e18

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector< pair<int, int> >> adj_list(n + 1, vector< pair<int, int> >());
    vector<int> d(n + 1, -INF);

    for (int i=0; i<e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({w, v});
    }

    int source; cout << "Enter Source : ";
    cin >> source;

    deque<int> q;
    d[source] = 0;
    q.push_back(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();

        for (auto& [w, v] : adj_list[u]) {
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (w) q.push_back(v);
                else q.push_front(v);
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int u; cin >> u;
        cout << d[u] << '\n';
    }


    return 0;
}