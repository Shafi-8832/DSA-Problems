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
#define int long long


class DSU {
    public:
    vector<int> parent;
    vector<int> group_size;
    int connected_components = 0;


    DSU(int n) {
        parent.resize(n + 1);
        group_size.resize(n + 1, 1);
        connected_components = n; // each vertex is a stand-alone component itself.

        for (int i=0; i<=n; i++) parent[i] = i; // each vertex is a parent to itself.
        // iota(parent.begin(), parent.end(), 0); same as parent[i] = i
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // path compression in one line for amortized O(1) TC
    }

    bool unite(int i, int j) {
        int parent_i = find(i);
        int parent_j = find(j);

        if (parent_i == parent_j) return false;

        if (group_size[parent_i] > group_size[parent_j]) {
            parent[parent_j] = parent_i;
            group_size[parent_i] += group_size[parent_j];
        }
        else {
            parent[parent_i] = parent_j;
            group_size[parent_j] += group_size[parent_i];
        }
        return true;
    }

    bool connected(int a, int b) {return find(a) == find(b); }
    int size(int a) { return group_size[find(a)]; }

    // IMPORTANT : when checking group_size or anything about DSU, always ask the parent, leader of the of the group.
    // NEVER ASK THE INDIVIDUAL node, they hold outdated values

};

typedef struct edge {
    int u, v, w;
    bool operator<(const edge& other) {
        return w < other.w;
    }
} edge;


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    
    int n, m; cin >> n >> m;

    // vector<vector<int>> adj_list(n, vector<int>());

    vector<edge> edges(m);

    for (int i=0; i<m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        // adj_list[u].pb({w, v});
    }

    sort(all(edges));

    // Krushkal
    DSU dsu(n); // batman
    int mst_weight = 0;
    int edges_taken = 0;

    for (auto& e : edges) {
        // pick an edge
        // check if that edges endpoints are already connected, hence creating a cycle

        // false --> already united
        // true --> was in different tree, and merged
        if (dsu.unite(e.u, e.v)) {
            mst_weight += e.w;
            edges_taken++;

            // NOTE : when n-1 edges have been taken, all the nodes are connected both in MST & prevailing DSU
            // so after this, the function will always reutrn false!
        }

        if (edges_taken == n-1) break;
    }

    // if the graph is disconnected to being with
    if (edges_taken != n-1) {
        cout << "IMPOSSIBLE\n";
    }
    else cout << mst_weight << '\n';

    return 0;
}