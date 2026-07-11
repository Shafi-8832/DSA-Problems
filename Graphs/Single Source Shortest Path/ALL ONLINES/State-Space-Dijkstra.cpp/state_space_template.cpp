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
#define INF INT64_MAX
#define int long long


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, e; cin >> n >> e;

    int MAX_COUPONS = 1;

    vector<vector<pii>> adjList(n + 1, vector<pii>());

    // THIS LINE
    vector<vector<int>> d(n + 1, vector<int>(MAX_COUPONS + 1, INF));
    // Shortest Path reconstruct

    vector<vector<pii>> parent(n + 1, vector<pii>(MAX_COUPONS + 1, {-1, -1}));

    int source; cin >> source;
    d[source][0] = 0;
    // for (int i=1; i<=MAX_COUPONS; i++) d[source][i] = INF; // Constructor alerady did it // just to clear the concept

    set<tiii> pq; // {d value, destination_node, coupon_status(used or not)}

    pq.insert({0, source, 0});
    
    while (!pq.empty()) {
        auto [dist, u, s] = *(pq.begin());
        pq.erase(pq.begin());

        for (auto &[w, v] : adjList[u]) {
            // HORIZONTAL WALK : up to u, joto gula coupon use korsi, u theke v te ashte ar use kori nai coupon
            if (d[v][s] > d[u][s] + w) {
                pq.erase({d[v][s], v, s}); // joto gula coupon used, toto gulai
                d[v][s] = d[u][s] + w;
                pq.insert({d[v][s], v, s}); // joto gula coupon used, toto gulai

                parent[v][s] = {u, s};

            }
            // Angled Edge / Lift
            if (s < MAX_COUPONS && d[v][s+1] > d[u][s] + w/2){
                pq.erase({d[v][s+1], v, s+1});
                d[v][s+1] = d[u][s] + w/2;
                pq.erase({d[v][s+1], v, s+1});

                parent[v][s+1] = {u, s};

            }
        }
    }

    int ans = INF;
    int coupon_used;
    for (int s = 0; s <= MAX_COUPONS; s++) {
        if (d[D][s] < ans) {
            ans = d[D][s];
            coupon_used = s;
        }
    }

    cout << D;
    cur = D;
    while (parent[cur][coupon_used].first != -1) {
        auto [u, s] = parent[cur][coupon_used];

        if (s == coupon_used) cout << "<--0---";
        else cout << "<---1---";

        coupon_used = s;
        cur = u;
        cout << u;
    }

    // vector<int> shortest_path;
    // int dest; cin >> dest;
    // for (int cur = dest; cur != -1; cur = parent[cur]) {
    //     shortest_path.pb(cur);
    // }
    // reverse(all(shortest_path));


    
    return 0;
}