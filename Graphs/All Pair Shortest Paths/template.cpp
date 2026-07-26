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


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    

    // input N, M, K . . . 
    int n, m; cin >> n >> m;

    // Initialize matrices (1-based indexing)
    vector<vector<long long>> dist(N + 1, vector<long long>(N + 1, INF)); // INDEX
    vector<vector<int>> nxt(N + 1, vector<int>(N + 1, -1)); // INDEX

    // 1. Base Setup
    for (int i = 1; i <= N; ++i) { // INDEX
        dist[i][i] = 0;
        nxt[i][i] = i; 
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long t;
        cin >> u >> v >> t;
        
        // Handle potential multiple edges between the same nodes by keeping the minimum
        if (t < dp[u][v]) {
            dp[u][v] = t; nxt[u][v] = v;
        
            // dp[v][u] = t; nxt[v][u] = u; // if undirected
        }
    }
    // dist[u][v] = weight; nxt[u][v] = v; // directed? only this line
    // dist[v][u] = weight; nxt[v][u] = u; // undirected? both lines


    for (int k = 1; k <= N; ++k) { // INDEX
        for (int i = 1; i <= N; ++i) { // INDEX
            for (int j = 1; j <= N; ++j) { // INDEX
                
                //integer overflow from adding to INF
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    long long new_dist = dist[i][k] + dist[k][j];
                    
                    if (new_dist < dist[i][j]) {
                        dist[i][j] = new_dist;
                        nxt[i][j] = nxt[i][k]; // First step from i to j is first step from i to k
                    }
                }
                
            }
        }
    }

    // for (int k = 1; k <= N; ++k) { // INDEX
    //     for (int i = 1; i <= N; ++i) { // INDEX
    //         // OPTIMIZATION: Start j at i + 1 to only scan the upper triangle for undirected graphs
    //         for (int j = i + 1; j <= N; ++j) { // INDEX            
    //             //integer overflow from adding to INF
    //             if (dist[i][k] != INF && dist[k][j] != INF) {
    //                 long long new_dist = dist[i][k] + dist[k][j];                
    //                 if (new_dist < dist[i][j]) {
    //                     // Update both halves of the distance matrix simultaneously
    //                     dist[i][j] = new_dist;
    //                     dist[j][i] = new_dist;                   
    //                     // Update both paths (pointing toward the bridge 'k')
    //                     nxt[i][j] = nxt[i][k]; 
    //                     nxt[j][i] = nxt[j][k]; 
    //                 }
    //             }           
    //         }
    //     }
    // }

    // path tracing

    int start, end;

    if (dist[start][end] == INF) {
        cout << "No path exists\n";
    } else {
        int current = start;
        do {
            cout << current << " -> ";
            current = next[current][end];
        } while (current != end);

        cout << end << '\n';
    }


    return 0;
}