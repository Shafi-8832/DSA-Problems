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

struct Point {int x, int y; };

int get_distance(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    
    
    int n; cin >> n;
    vector<Point> cities(n);
    for (int i=0; i<n; i++) cin >> cities[i].x >> cities[i].y;
    
    vector<int> in_mst(n, false);
    vector<int> min_cost(, 2e9); // min_cost[v] = the lightest cross edge from S connecting to v
    vector<int> parent(n, -1);


    min_cost[0] = 0;
    int mst = 0;
    in_mst[0] = true;

    for (int i=0; i<n; i++) { // for all n nodes

        // finding the lighest cross edge (the safe edge to add to the growing MST / the set S)
        int u = -1;
        for (int j=0; j<n; j++) {
            if (!in_mst[j] && (u == -1 || min_cost[j] < min_cost[u])) {
                u = j;
            }
        }

        // now we have the index of the lightest cross edge

        if (min_cost[u] == 2e9) return -1;


        // Conquer the city!
        in_mst[u] = true;
        mst += min_cost[u];


        // v changing, u constant here
        // standing from city u, I look at the cities outside (V\S)
        for (int v=0; v<n; v++) { // since u has been conquered, search outer 
            if (in_mst[v]) continue; // search outer

            int cost = get_distance(cities[u], cities[v]);
            if (cost < min_cost[v]) min_cost[v] = cost, parent[v] = u;
        }
    }

    cout << mst << '\n';
    


    return 0;
}