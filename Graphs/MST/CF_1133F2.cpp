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

    int n, m, D; cin >> n >> m >> D;
    vector<pair<int, int>> edges(m);


    vector<int> adj1;

    for (int i=0; i<m; i++) {
        cin >> edges[i].first >> edges[i].second;
        if (edges[i].first == 1 || edges[i].second == 1) adj1.pb(edges[i].first + edges[i].second - 1);
    }

    int k = adj1.size();

    if (k < D) {
        cout << "NO\n";
        return 0;
    }

    DSU dsu(n);

    vector<pair<int, int>> final_edges;

    // since any MST, skip sorting
    for (auto& e : edges) {
        if (e.first == 1 || e.second == 1) continue;
        dsu.unite(e.first, e.second); // edge has been picked up
    }

    // after this, we have C components that are actually little forests. (C >= 1, C can be 1 too)
    // the only way to go from one forest to another is through vertex 1 
    // (think about it, if there were a way bypassing vertex 1, then that should have been added by the DSU batman)

    int C = dsu.connected_components - 1; // internally counted, check the DSU class and excluding vertex 1

    if (D < C) {
        cout << "NO\n";
        return 0;
    }

    DSU dsu2(n);

    vector<bool> used_neighbor(n + 1, false);

        // optimization possible??
        // what if I store vertex 1's adjacency only?? did, doesn't hurt
        for (auto& v : adj1) {
            if (dsu.unite(1, v)) {
                dsu2.unite(1, v); // returns true as dsu2 layer is started off empty
                final_edges.pb({1, v});
                used_neighbor[v] = true;
            }
        }

        // now think, dsu2 only knows the 1 to v edges connections!
        
        int degree_so_far = C;
        // vertex 1 has an exact degree of C

        for (auto& v : adj1) {
            if (degree_so_far == D) break; // why put it inside the first line as the for loop, if degree_so_far == D already, it breaks the second for loop and goes to add internal edges, a tricky syntactical move.
            if (!used_neighbor[v]) {
                final_edges.pb({1, v});
                degree_so_far++;
                dsu2.unite(1, v); // returns true always, since dsu2 only knows the 1 to v edges first
            }
        }

    for (auto& e : edges) {
        if (e.first == 1 || e.second == 1) continue;
        if (dsu2.unite(e.first, e.second)) final_edges.pb({e.first, e.second});
        // reject if cycle
    }


    if (final_edges.size() == n - 1) {
        cout << "YES\n";
        for (auto& t : final_edges) {
            cout << t.first << " " << t.second << '\n';
        }
    } else cout << "NO\n";



    return 0;
}