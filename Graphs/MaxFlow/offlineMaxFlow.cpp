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

typedef struct {
    string id;
    string dep_city; // or char
    string arr_city;

    int dep_time;
    int arr_time;
} Flight;

int bfs(int source, int dest, vector<int>& parent, vector<vector<int>>& curr_cap, vector<vector<int>>& adj_list) {
    int n = parent.size();

    queue<int>q;
    q.push(source);

    vector<bool> visited(n, false);
    visited[source] = true;

    vector<int> min_cap(n);
    min_cap[source] = INT_MAX; // infinite water glitch

    while (!q.empty()) {
        int u=q.front();
        q.pop();
        if (u == dest) return min_cap[u];

        for (int v : adj_list[u]) {
            if (!visited[v] && curr_cap[u][v] > 0) {
                visited[v] = true;
                
                parent[v] = u;
                min_cap[v] = min(min_cap[u], curr_cap[u][v]);
                
                q.push(v);
            }
        }
    }

    return -1;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int F; cin >> F;
    vector<Flight> flights(F);

    for (int i=0; i<F; i++) {
        string id, dep_city, arr_city;
        int hh, mm;
        char colon;

        cin >> id >> dep_city >> arr_city;

        cin >> hh >> colon >> mm;
        flights[i].arr_time = hh * 60 + mm;
        
        cin >> hh >> colon >> mm;
        flights[i].dep_time = hh * 60 + mm;

        flights[i].id = id;
        flights[i].dep_city = dep_city;
        flights[i].arr_city = arr_city;
    }

    int total_vertices = 2*F + 2; // 0 , 1 ---- F F + 1 ----- 2F, 2F + 1
    vector<vector<int>> adj_list(total_vertices, vector<int>());
    vector<vector<int>> capacity(total_vertices, vector<int>(total_vertices, 0));
    vector<vector<int>> curr_cap(total_vertices, vector<int>(total_vertices, 0));
    vector<int> parent(total_vertices, -1);

    vector<pii> valid_edges;

    // Middle edges generation
    for (int i=0; i<F; i++) {
        for (int j=0; j<F; j++) {

            if (i == j) continue; // can't connect a flight with itself

            if (flights[i].arr_city == flights[j].dep_city
            && flights[i].arr_time + 180 <= flights[j].dep_time) {
                
                int left_node = i + 1;
                int right_node = j + F + 1;

                capacity[left_node][right_node] = 1; // 
                curr_cap[left_node][right_node] = 1;

                adj_list[left_node].pb(right_node);
                adj_list[right_node].pb(left_node); // reverse_edge

                valid_edges.pb({left_node, right_node});
            }
        }
    }

    // source to every first flight/ V_out
    for (int i=1; i<=F; i++) {
        capacity[0][i] = 1;
        curr_cap[0][i] = 1;

        adj_list[0].pb(i);
        adj_list[i].pb(0);
    }

    // every second flight to target/ V_in
    for (int i=F+1; i<=2*F; i++) {
        capacity[i][2*F + 1] = 1;
        curr_cap[i][2*F + 1] = 1;

        adj_list[i].pb(2 * F + 1);
        adj_list[2 * F + 1].pb(i);
    }

    int maxFlow = 0;
    int bottleneck = 0;

    int source = 0;
    int dest = total_vertices-1; // 2F - 1
    
    while ((bottleneck = bfs(source, dest, parent, curr_cap, adj_list)) != -1) {
        maxFlow += bottleneck; // corollary 26.3

        // trace the AUGMENTED path
        int cur = dest;
        while (parent[cur] != -1) {
            int from = parent[cur];
            int to = cur;

            // edge (from, to)
            curr_cap[from][to] -= bottleneck;
            curr_cap[to][from] += bottleneck;

            cur = from;
        }

        fill(all(parent), -1);
    }

    // can't dynamically build the aircraft assigning because, Edmond Karp is working on AUGMENTED paths, not actual paths in the graph.
    // I must wait until the algorithm is finished

    // for (int i=1; i<=F; i++) {
    //     for (int j=F+1; j<=2*F; j++) {

    //         if (curr_cap[i][j] == 0 && capacity[i][j] == 1) {

    //         }
    //     }
    // }

    cout << "Number of Aircrafts : " << F - maxFlow << '\n';
    // cout << maxFlow << '\n';

    vector<int> next_flight(F + 1, -1); // no node in "IN Set" can be pointed by multiple nodes in "OUT Set"
    vector<bool> has_prev(F + 1, false); // no node in "IN Set" can point multiple nodes in "OUT Set"

    for (auto edge : valid_edges) {
        int from = edge.first;
        int to = edge.second;

        if (curr_cap[from][to] == 0) { // if 0 then picked up by Edmond-Karp
            next_flight[from] = to - F;
            has_prev[to-F] = true;
        }
    }

    int aircraft = 0;
    for (int i=1; i<=F; i++) {
        if (!has_prev[i]) { // i must be the start of a disjoint chain of flights for one aircraft
            aircraft++;
            cout << "Aircraft " << aircraft << ": ";

            // a disjoint chain = a disjoint complete route for an aircraft
            // print the disjoint chain of flights built in <next_flight> for this current aircraft
            int curr = i;
            while (next_flight[curr] != -1) {
                cout << flights[curr-1].id << " -> ";
                curr = next_flight[curr];
            }
            cout << flights[curr-1].id << '\n';
        }
    }


    return 0;
}