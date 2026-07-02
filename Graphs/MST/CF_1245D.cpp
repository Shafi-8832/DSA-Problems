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

template <class T>
ostream& operator<<(ostream& os, vector<T>& vec) {
    for (auto& t : vec) os << t << " ";
    os << '\n';
    return os;
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    

    int n; cin >> n; //number of cities
    vector<pair<int, int>> cities(n + 1);
    // for (auto& c : cities) { // eije fatal error, city to n ta actually, n + 1 nile to input nibe n + 1 ta, cf to input n tai dibe!!
    //     cin >> c.first >> c.second;
    // }

    for (int i=1; i<=n;i++) cin >> cities[i].first >> cities[i].second;

    vector<int> city_cost(n + 1);
    // for (auto& c : city_cost) cin >> c;
    for (int i=1; i<=n; i++) cin >> city_cost[i];

    vector<int> k(n + 1); // Common Mistake : if you take an empty vector, then the range based for loop will not take ANY input!!!!
    // for (auto& km : k) cin >> km;
    for (int i=1; i<=n; i++) cin >> k[i];

    DSU dsu(n);

    vector<tuple<int, int, int>> edges;

    // wire generation
    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) {
            int x1 = cities[i].first;
            int y1 = cities[i].second;

            int x2 = cities[j].first;
            int y2 = cities[j].second;

            int weight = abs(x1 - x2) + abs(y1 - y2);
            weight = weight * (k[i] + k[j]);

            edges.push_back({weight, i, j});
        }
    }

    // wire generation from Super Plant Node 0
    for (int i = 1; i<= n; i++) {
        edges.push_back({city_cost[i], 0, i});
    }

    sort(all(edges));

    int mst_weight = 0;
    int power_stations = 0;
    vector<int> ps;
    int number_of_connections = 0;
    vector<pair<int, int>> cn;

    int edges_taken = 0;

    for (auto& e : edges) {
        int w = get<0>(e);
        int u = get<1>(e);
        int v = get<2>(e);

        if ( dsu.unite( u , v )) {
            mst_weight += w;
            edges_taken++;

            // edge saving
            if (u == 0 || v == 0) { // the super plant!
                power_stations++;
                ps.pb(u + v); // either of them must be 0
            }
            else {
                number_of_connections++;
                cn.pb({u, v});
            }
        }
        if (edges_taken == n) break; // Common Mistake, n + 1 nodes! with the super plant!
    }

    cout << mst_weight << '\n';
    cout << power_stations << '\n';
    for (auto& p : ps) {
        cout << p << " ";
    }
    cout << '\n';

    cout << number_of_connections << '\n';
    for (auto& p : cn) {
        cout << p.first << " " << p.second << '\n';
    }


    return 0;
}