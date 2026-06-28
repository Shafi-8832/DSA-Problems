#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9;

// We need to know the absolute maximum edge weight (k) in advance.
// For this example, let's assume no edge weight is greater than 10.
const int K = 10; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; 
    cin >> n >> m;

    // Adjacency list: {weight, neighbor}
    vector<vector<pair<int, int>>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }

    vector<int> dist(n + 1, INF);
    
    // The "Buckets". We need exactly K + 1 buckets.
    vector<queue<int>> buckets(K + 1);
    
    // We track total active elements to know when the algorithm is completely finished.
    int active_elements = 0;
    
    // Our absolute tracker for the distance we are currently evaluating.
    int current_dist = 0;

    // Initialization
    dist[1] = 0;
    buckets[0].push(1);
    active_elements++;

    // Run until there are no more nodes waiting in any bucket
    while (active_elements > 0) {
        
        // 1. SPIN THE POINTER
        // If the bucket for our current distance is empty, just increment the distance.
        // The modulo operator (current_dist % (K + 1)) automatically wraps the array around in a circle!
        while (buckets[current_dist % (K + 1)].empty()) {
            current_dist++;
        }

        // 2. EXTRACT THE NODE
        int u = buckets[current_dist % (K + 1)].front();
        buckets[current_dist % (K + 1)].pop();
        active_elements--; // We took a node out

        // 3. THE LAZY DELETION CHECK (Crucial!)
        // Just like standard Dijkstra, if we pop an old, worse distance, throw it away.
        // We know it's worse if the recorded dist[u] is strictly less than the bucket it was sitting in.
        if (dist[u] < current_dist) continue;

        // 4. RELAX EDGES
        for (auto& edge : adj[u]) {
            int w = edge.first;
            int v = edge.second;

            if (current_dist + w < dist[v]) {
                dist[v] = current_dist + w;
                
                // Drop the neighbor into its corresponding future bucket using modulo!
                buckets[dist[v] % (K + 1)].push(v);
                
                active_elements++; // We added a node in
            }
        }
    }

    // Output results
    for(int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << "\n";

    return 0;
}