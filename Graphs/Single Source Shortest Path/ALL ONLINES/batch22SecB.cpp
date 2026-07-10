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
#define intmax INT64_MAX
#define int long long

 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k, b, e; cin >> n >> m >> k >> b >> e;
    vector<int> d(n + 1, intmax);
    for (int i=0; i<k; i++) {
        int cap; cin >> cap;
        d[cap] = 0;
    }

    vector<bool> blocked(n + 1, false);
    // bitset<MAX_NODES>block(n+1, false);

    if (b==0) cin.ignore();
    else {
        for (int i=0; i<b; i++) {int bl; cin >> bl; blocked[bl] = true;}
    }   

    vector<int> destinations;
    for (int i=0; i<e; i++) {
        int emer; cin >> emer;
        destinations.pb(emer);
    }

    vector<tiii> edges; // edges(m) leikha abar push_back korte gesi common mistake
    for (int i=0; i<m; i++) {
        int u, v, w; cin >> u >> v >> w;
        if (blocked[u] || blocked[v]) continue;
        edges.pb({u, v, w});
    }

    bool ektao_edge_relax_hoe_nai = true;
    for (int i=1; i<=n-1; i++) {
        for (auto& e : edges) {
            int u = get<0>(e);
            int v = get<1>(e);
            int w = get<2>(e);

            if (d[u] != intmax && d[v] > d[u] + w) {
                d[v] = d[u] + w;
                ektao_edge_relax_hoe_nai = false; // relax hoise current round e
            } 
        }
        // ei round e jodi . . .
        if (ektao_edge_relax_hoe_nai) break;
    }

    bool abyss = false;
    for (auto& e : edges) { 
        int u = get<0>(e); 
        int v = get<1>(e);
        int w = get<2>(e);

        if (d[u] != intmax && d[v] > d[u] + w) {
            abyss = true;
            break;
        } 
    }

    if (abyss) {
        cout << "Abyss Detected\n";
    }
    else {
        for (auto& dest : destinations) {
            cout << dest << "->";
            if (d[dest] == intmax) cout << "INF";
            else cout << d[dest];
            cout << '\n';
        }
    }

    
    return 0;
}