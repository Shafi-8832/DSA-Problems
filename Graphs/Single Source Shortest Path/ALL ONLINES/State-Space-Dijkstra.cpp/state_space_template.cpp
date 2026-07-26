#include<bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>; 

#define f(t, i, x, y) for (t (i)=(x); (i)<(y); (i)++)
#define fe(t, i, x, y) for (t (i)=(x); (i)<=(y); (i)++)

#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define intmin INT64_MIN
#define INF INT64_MAX
#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, e; 
    if (!(cin >> n >> e)) return 0;

    int MAX_COUPONS = 1;

    vector<vector<pii>> adjList(n + 1, vector<pii>());
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].pb({w, v});
        adjList[v].pb({w, u}); // Assuming bidirectional, remove if directed
    }

    // 2D Distance Array: d[node][coupons_used]
    vector<vector<int>> d(n + 1, vector<int>(MAX_COUPONS + 1, INF));
    
    // Parent Array: parent[node][coupons_used] = {prev_node, prev_coupons_used}
    vector<vector<pii>> parent(n + 1, vector<pii>(MAX_COUPONS + 1, {-1, -1}));

    int source, D; 
    cin >> source >> D;
    
    d[source][0] = 0;

    set<tiii> pq; // {d value, destination_node, coupon_status}
    pq.insert({0, source, 0});
    
    while (!pq.empty()) {
        auto [dist, u, s] = *(pq.begin());
        pq.erase(pq.begin());

        // We do NOT break early, to allow all parallel states to reach D!

        for (auto &[w, v] : adjList[u]) {
            // HORIZONTAL WALK: No new coupons used
            if (d[v][s] > d[u][s] + w) {
                pq.erase({d[v][s], v, s}); 
                d[v][s] = d[u][s] + w;
                pq.insert({d[v][s], v, s}); 
                parent[v][s] = {u, s};
            }
            
            // DIAGONAL LIFT: Use exactly 1 coupon
            if (s < MAX_COUPONS && d[v][s+1] > d[u][s] + (w / 2)){
                pq.erase({d[v][s+1], v, s+1});
                d[v][s+1] = d[u][s] + (w / 2);
                pq.insert({d[v][s+1], v, s+1}); 
                parent[v][s+1] = {u, s};
            }
        }
    }

    int ans = INF;
    int curr_s = 0;
    
    for (int s = 0; s <= MAX_COUPONS; s++) {
        if (d[D][s] < ans) {
            ans = d[D][s];
            curr_s = s; 
        }
    }

    if (ans == INF) {
        cout << "Not Possible\n";
        return 0;
    }

    // Path Reconstruction
    vector<pii> path; // {node, coupons_spent_to_arrive_here}
    int cur = D;
    
    while (parent[cur][curr_s].first != -1) {
        auto [prev_node, prev_node_s] = parent[cur][curr_s];
        
        // Calculate exactly how many coupons were spent on this specific road
        int coupons_spent = curr_s - prev_node_s; 
        
        path.pb({cur, coupons_spent});
        
        cur = prev_node;
        curr_s = prev_node_s;
    }

    path.pb({source, 0}); // Push the starting node (0 coupons spent to arrive at source)
    reverse(all(path));

    // Print forwards
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i].first;
        if (i < path.size() - 1) {
            cout << " --" << path[i+1].second << "--> ";
        }
    }
    cout << "\nTotal Cost: " << ans << "\n";

    return 0;
}