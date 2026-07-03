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
    
    int n; cin >> n;
    vector<pii> points(n);
    for (auto& p : points) {
        cin >> p;
    }

    vector<tiii> edges;
    // generate all edges
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            int x1 = points[i].first;
            int y1 = points[i].second;

            int x2 = points[j].first;
            int y2 = points[j].second;

            int w = abs(x1 - x2) + abs(y1 - y2);

            edges.pb({w, i, j});
        }
    }

    sort(all(edges));
    int mst = 0;
    int edges_taken = 0;
    bool possible = true;

    DSU dsu(n);
    for (auto& e : edges) {
        int w = get<0>(e);
        int a = get<1>(e);
        int b = get<2>(e);

        if (dsu.unite(a, b)) {
            mst += w;
            edges_taken++;

            if (edges_taken == n - 1) {
                possible = true;
                break;
            }
        }
    }

    if (!possible) {
        cout << -1 << '\n';
    }

    cout << mst << '\n';

    return 0;
}