#include "bits/stdc++.h"

using namespace std;

int main() {
    int n, m; cin >> n >> m;

    if (n > m) {
        cout << n-m;
        return 0;
    }

    // unordered_map<int, int> dist; // dist + visited both
    vector<int> dist(20005, -1);

    queue<int> q;
    q.push(n);
    dist[n] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == m) {
            cout << dist[u];
            return 0;
        }

        // 2 neighbours

        if (2 * u <= 20000 && dist[2*u] == -1) q.push(2 * u), dist[2 * u] = dist[u] + 1;

        if (u - 1 > 0 && dist[u-1] == -1) q.push(u - 1), dist[u-1] = dist[u] + 1;
    }
    return 0;
}
