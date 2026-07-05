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
    vector<int> safe_count;
    int connected_components;
    int max_size = 1;
    int largest_leader = 1;


    DSU(int n) {
        parent.resize(n + 1);
        group_size.resize(n + 1, 1);
        safe_count.resize(n + 1, 0);

        connected_components = n; // each vertex is a stand-alone component itself.

        for (int i=0; i<=n; i++) parent[i] = i; // each vertex is a parent to itself.
        // iota(parent.begin(), parent.end(), 0); same as parent[i] = i

        // count safe nodes here
        for (int i=0; i<=n; i++) {
            if (/*condition to be safe node*/) safe_count[i] = 1;
        }
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
            safe_count[parent_i] += safe_count[parent_j];

            if (group_size[parent_i] > max_size) {
                max_size = group_size[parent_i];
                largest_leader = parent_i;
            }
        }
        else {
            parent[parent_i] = parent_j;
            group_size[parent_j] += group_size[parent_i];
            safe_count[parent_j] += safe_count[parent_i];


            if (group_size[parent_i] > max_size) {
                max_size = group_size[parent_i];
                largest_leader = parent_i;
            }
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

class Edge {
    public: 
    int u, v;
    int original_weight;
    int risky_points;
    int effective_weight;

    Edge(int U, int V, int org, int rp, int P) {
        u = U;
        v = V;
        original_weight = org;
        risky_points = rp;

        effective_weight = original_weight + P * risky_points;
    }

    bool operator<(const Edge& other) {
        bool this_safe = (risky_points == 0);
        bool other_safe = (other.risky_points == 0);

        if (this_safe != other_safe) {
            return this_safe > other_safe;
        }

        return effective_weight < other.effective_weight;
    }
};



int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    
    return 0;
}