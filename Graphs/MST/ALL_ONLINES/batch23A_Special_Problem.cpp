#include<bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
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
    int connected_components;
    int max_size = 1;


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

        if (parent_i == parent_j) return false; // didn't change the component_count, cause same tree

        if (group_size[parent_i] > group_size[parent_j]) {
            parent[parent_j] = parent_i;
            group_size[parent_i] += group_size[parent_j];


            max_size = max(max_size, group_size[parent_i]);
        }
        else {
            parent[parent_i] = parent_j;
            group_size[parent_j] += group_size[parent_i];


            max_size = max(max_size, group_size[parent_j]);
        }

        // successfully merged two groups == edge created between two forests so,,,
        connected_components--;

        return true; // yeah, they were in different component, successfully connected
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

    vector<pii> type3;
    vector<pii> type2;
    vector<pii> type1;
    for (int i=0; i<m; i++) {
        int a, b, c; cin >> a >> b >> c;

        if (c == 3) type3.pb({a, b});
        else if (c == 2) type2.pb({a, b});
        else if (c == 1) type1.pb({a, b});
    }

    DSU dsu_men(n), dsu_women(n);

    int total_edges = 0;

    for (auto& e : type3) {
        int a = e.first, b = e.second;
        bool men = dsu_men.unite(a, b);
        bool women = dsu_women.unite(a, b);

        if (men || women) total_edges++; // Concept*** : actually both men & women will be either true OR false, T, F or F, T not possible
    }

    for (auto& e : type1) {
        int a = e.first, b = e.second;
        if (dsu_men.unite(a, b)) {
            total_edges++;
        }
    }

    for (auto& e : type2) {
        int a = e.first, b = e.second;
        if (dsu_women.unite(a, b)) {
            total_edges++;
        }
    }

    if (dsu_men.connected_components == dsu_women.connected_components) {
        cout << m - total_edges << '\n';
    }
    else cout << -1 << '\n';

    return 0;
}