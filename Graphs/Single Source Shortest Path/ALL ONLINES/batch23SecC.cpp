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
#define INF INT64_MAX


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int MAX_COUPONS = 1;
    int n, e; cin >> n >> e;
    vector<vector<pii>> adj(n + 1, vector<pii>());
    vector<vector<pii>> adjRev(n + 1, vector<pii>()); // The reversed graph

    vector<vector<int>> d_fwrd(n + 1, vector<int>(MAX_COUPONS + 1, INF)); // constructor does the job, don't worry
    vector<vector<int>> d_rev(n + 1, vector<int>(MAX_COUPONS + 1, INF));

    for (int i=0; i<e; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].pb({c, b});
        adjRev[b].pb({c, a});
    }

    int x, y, w; cin >> x >> y >> w;
    tiii must_edge = {x, y, w};
    dest_fwrd = x;
    dest_rev = y;

    // dijkstra 1
    set<tiii> pq_fwrd;
    d_fwrd[1][0] = 0;
    pq_fwrd.insert({0, 1, 0});
    while (!pq_fwrd.empty()) {
        auto [dist, u, s] = *pq_fwrd.begin();
        pq_fwrd.erase(pq_fwrd.begin());

        // if (u == dest_rev) break; FATAL ERROR ! : you can't terminate early in state-space dijkstra!

        for (auto& [w, v] : adj[u]) {
            // hori
            if (d_fwrd[v][s] > d_fwrd[u][s] + w) {
                pq_fwrd.erase({d_fwrd[v][s], v, s});
                d_fwrd[v][s] = d_fwrd[u][s] + w;
                pq_fwrd.insert({d_fwrd[v][s], v, s});

                // parent pointer
            }
            if (s < MAX_COUPONS && d_fwrd[v][s+1] > d_fwrd[u][s] + w/2) {
                pq_fwrd.erase({d_fwrd[v][s+1], v, s+1});
                d_fwrd[v][s+1] = d_fwrd[u][s] + w/2;
                pq_fwrd.insert({d_fwrd[v][s+1], v, s+1});

                // parent pointer
            }
        }
    }

    //dijkstra 2
    set<tiii> pq_rev;
    d_rev[n][0] = 0;
    pq_rev.insert({0, n, 0});
    while (!pq_rev.empty()) {
        auto [dist, u, s] = *pq_rev.begin();
        pq_rev.erase(pq_rev.begin());

        // if (u == dest_rev) break; FATAL ERROR ! : you can't terminate early in state-space dijkstra!

        for (auto& [w, v] : adjRev[u]) {
            // hori
            if (d_rev[v][s] > d_rev[u][s] + w) {
                pq_rev.erase({d_rev[v][s], v, s});
                d_rev[v][s] = d_rev[u][s] + w;
                pq_rev.insert({d_rev[v][s], v, s});

                // parent pointer
            }
            if (s < MAX_COUPONS && d_rev[v][s+1] > d_rev[u][s] + w/2) {
                pq_rev.erase({d_rev[v][s+1], v, s+1});
                d_rev[v][s+1] = d_rev[u][s] + w/2;
                pq_rev.insert({d_rev[v][s+1], v, s+1});

                // parent pointer
            }
        }
    }


    int cost = INF;


    if (d_fwrd[dest_fwrd][1] != INF && d_rev[dest_rev][0] != INF) {
        cost = min(cost, d_fwrd[dest_fwrd][1] + w + d_rev[dest_rev][0]);
    }
    if (d_fwrd[dest_fwrd][0] != INF && d_rev[dest_rev][0] != INF) {
        cost = min(cost, d_fwrd[dest_fwrd][0] + w/2 + d_rev[dest_rev][0]);
    }
    if (d_fwrd[dest_fwrd][0] != INF && d_rev[dest_rev][1] != INF) {
        cost = min(cost, d_fwrd[dest_fwrd][0] + w + d_rev[dest_rev][1]);
    }


    cout << cost;

    return 0;
}