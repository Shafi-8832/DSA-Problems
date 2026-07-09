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


struct planet {
    int x, y, z;
    int id;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    

    // PROBLEM NOTE : normally between two nodes u and v, there can be any weight w, be it 10, 100, 0, 1, whatever
    // but when you define the weight to be the distance between two points, then the weights just can't be "anything"
    // the weights become definite
    // point A, point B
    // the weight is their distance = dA - dB, it is never random, it is "definite"
    // let say you all points in the X axis
    // A ----5------ B ----------7---------- C
    // then you never need to generate A to C edge cuz it's 12 and not visiting B node anyway, DSU will not choose it
    // DSU will choose A to B and B to C edges anyway, it will never choose A to C edge.


    int n; cin >> n;
    vector<planet> points(n);
    for (int i=0; i<n; i++) {
        cin >> points[i].x >> points[i].y >> points[i].z;
        points[i].id = i;
    }

    vector<tiii>edges;

    sort(all(points), [](const planet& a, const planet& b) { return a.x < b.x; });

    for (int i=0; i<n-1; i++) {
        int u = points[i].id;
        int v = points[i + 1].id;
        int w = abs(points[i].x - points[i + 1].x);
        edges.pb({w, u, v});
    }

    sort(all(points), [](const planet& a, const planet& b) { return a.y < b.y; });

    for (int i=0; i<n-1; i++) {
        int u = points[i].id;
        int v = points[i + 1].id;
        int w = abs(points[i].y - points[i + 1].y);
        edges.pb({w, u, v});
    }

    sort(all(points), [](const planet& a, const planet& b) { return a.z < b.z; } );

    for (int i=0; i<n-1; i++) {
        int u = points[i].id;
        int v = points[i + 1].id;
        int w = abs(points[i].z - points[i + 1].z);
        edges.pb({w, u, v});
    }

    sort(all(edges));

    DSU dsu(n);
    int mst = 0;
    int edges_taken = 0;

    for (auto& e : edges) {
        int w = get<0>(e);
        int u = get<1>(e);
        int v = get<2>(e);

        if (dsu.unite(u, v)) {
            mst += w;
            edges_taken++;
            
            if (edges_taken == n-1) break;
        }
    }

    cout << mst << '\n';

    return 0;
}