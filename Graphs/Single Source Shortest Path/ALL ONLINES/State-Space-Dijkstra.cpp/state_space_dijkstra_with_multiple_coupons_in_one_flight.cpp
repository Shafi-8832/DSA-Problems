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

    int MAX_COUPONS = 3; // Example: Allow up to 3 stacked coupons

    vector<vector<pii>> adjList(n + 1, vector<pii>());
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].pb({w, v});
    }

    vector<vector<int>> d(n + 1, vector<int>(MAX_COUPONS + 1, INF));
    vector<vector<pii>> parent(n + 1, vector<pii>(MAX_COUPONS + 1, {-1, -1}));

    int source, D; 
    cin >> source >> D;
    
    d[source][0] = 0;

    set<tiii> pq; 
    pq.insert({0, source, 0});
    
    while (!pq.empty()) {
        auto [dist, u, s] = *(pq.begin());
        pq.erase(pq.begin());

        for (auto &[w, v] : adjList[u]) {
            int coupon_left = MAX_COUPONS - s;
            
            // Loop through all allowable coupon spends on this single edge!
            for (int c = 0; c <= coupon_left; c++) {
                int next_s = s + c;
                int eff_weight = w >> c; // Stacked discount: w / (2^c)

                if (d[v][next_s] > d[u][s] + eff_weight) {
                    pq.erase({d[v][next_s], v, next_s});
                    d[v][next_s] = d[u][s] + eff_weight;
                    pq.insert({d[v][next_s], v, next_s});

                    parent[v][next_s] = {u, s};
                }
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

    vector<pii> path; 
    int cur = D;
    
    while (parent[cur][curr_s].first != -1) {
        auto [prev_node, prev_node_s] = parent[cur][curr_s];
        
        // This easily catches exactly how many coupons were stacked here
        int coupons_spent = curr_s - prev_node_s; 

        path.pb({cur, coupons_spent});

        cur = prev_node;
        curr_s = prev_node_s;
    }

    path.pb({source, 0}); 
    reverse(all(path));

    // Print forwards seamlessly
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i].first;
        if (i < path.size() - 1) {
            cout << " --" << path[i+1].second << "--> ";
        }
    }
    cout << "\nTotal Cost: " << ans << "\n";

    return 0;
}