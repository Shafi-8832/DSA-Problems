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
    vector<int> safe_count; //


    DSU(int n, vector<bool>& risky) {
        parent.resize(n + 1);
        group_size.resize(n + 1, 1);
        connected_components = n; // each vertex is a stand-alone component itself.



        safe_count.resize(n + 1, 0);

        for (int i=0; i<=n; i++) {
            parent[i] = i; // each vertex is a parent to itself.

            if (i < n && !risky[i]) safe_count[i] = 1;
        }
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


            safe_count[parent_i] += safe_count[parent_j];
        }
        else {
            parent[parent_i] = parent_j;
            group_size[parent_j] += group_size[parent_i];
            max_size = max(max_size, group_size[parent_j]);


            safe_count[parent_j] += safe_count[parent_i];
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
    int u, v;

    int original_weight;
    int risky_points; // 0 1 2
    int effective_weight;


    bool operator<(const edge& other) {
        bool this_safe = (risky_points == 0);
        bool other_safe = (other.risky_points == 0);

        if (this_safe != other_safe) {
            return this_safe > other_safe;
        }

        return effective_weight < other.effective_weight;
    }
} edge;



int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    
    int n, m, p, k;
    cin >> n >> m >> p;

    cin >> k;

    vector<bool> risky(n, false);
    for (int i=0; i<k; i++) {
        int x;
        cin >> x;
        risky[x] = true;
    }

    vector<edge> edges(m);
    for (auto& e : edges) {
        cin >> e.u >> e.v >> e.original_weight;
        e.risky_points = (risky[e.u]) + (risky[e.v]);

        e.effective_weight = e.original_weight + P * e.risky_points; // 
    }

    sort(all(edges));

    int cost = 0;
    vector<pair<int, int>> final_edges;


    DSU dsu(n, risky);

    bool possible = false;

    for (auto& e : edges) {
        int u = e.u, v = e.v, w = e.effective_weight;

        if (dsu.unite(u, v)) {
            final_edges.pb({u, v});
            cost += w;

            if (dsu.safe_count[dsu.find(u)] == n-k) {
                possible = true;
                break;
            }
        }
    }

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    cout << final_edges.size() << '\n';

    for (auto& e : final_edges) {
        cout << e.first << " " << e.second;
        cout << (risky[e.first] || risky[e.second]) ? "RISKY\n" : "\n";
    }
    cout << cost;
 

    return 0;
}