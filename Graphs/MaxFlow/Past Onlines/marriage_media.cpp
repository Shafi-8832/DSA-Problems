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

typedef struct person {
    string gender;
    int age;
    int height;
    bool is_divorced;
} person;


typedef struct edge {
    int to; 
    int capacity;
    int rev_index; // so that I can jump adj[to][rev_index] = from;
    // 
};

bool bfs(int source, int sink, vector<vector<edge>>& adjList, vector<pii>& parent) {
    int n = parent.size();
    vector<bool> visited(n, false);
    visited[source] = true;
    // vector<int> min_cap(n);
    // min_cap[source] = INT64_MAX;

    queue<int> q;
    q.push(source);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == sink) return 1;

        for (int i=0; i<adjList[u].size(); i++) {
            int v = adjList[u][i].to;
            int edge_capacity = adjList[u][i].capacity;

            if (!visited[v] && edge_capacity > 0) {
                parent[v] = {u, i};
                q.push(v);
                visited[v] = true;

                // min_cap[v] = edge_capacity; // either bottleneck 1 .... wait, I don't need it, all augmented paths will have bottleneck 1! bruhh
            }
        }
    }

    return 0;
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int t; cin >> t;

    int m, n; cin >> m >> n;
    vector<person> people(m + n);

    for (int i=0; i<m+n; i++) { // Men (0 to m-1) & Women (m to m + n - 1)

        cin >> people[i].height;
        cin >> people[i].age;
        if (i <= m-1) people[i].gender = "M";
        else people[i].gender = "F";
        cin >> people[i].is_divorced;

    }

    vector<vector<edge>> adjList(1 + m + n + 1, vector<edge>());

    vector<pii> parent(m+n+2, {-1, -1});

    for (int i=0; i<=m-1; i++) { // Men
        for (int j=m; j<=m+n-1; j++) { // Women
            if (abs(people[i].height - people[j].height) <= 12 && 
                abs(people[i].age - people[j].age) <= 5 && 
                people[i].is_divorced == people[j].is_divorced) {
                    adjList[i+1].pb({j+1, 1, adjList[j+1].size()});

                    adjList[j+1].pb({i+1, 0, adjList[i+1].size() - 1});
                }
        }
    }

    // source to every man
    for (int i=1; i<=m; i++) {
        adjList[0].pb({i, 1, adjList[i].size()});
        adjList[i].pb({0, 0, adjList[0].size() - 1});
    }
    
    int source = 0;
    int sink = m + n + 1;
    // every woman to sink
    for (int j=m+1; j<=m+n; j++) {

        adjList[j].pb({sink, 1, adjList[sink].size()});
        adjList[sink].pb({j, 0, adjList[j].size() - 1});
    }

    // Done building the graph

    int maxFlow = 0;
    // int bottleneck = 0;

    while (bfs(source, sink, adjList, parent)) {
        // maxFlow += bottleneck;
        maxFlow++;

        int cur = sink;
        while (parent[cur].first != -1) {
            int from = parent[cur].first;
            int to = cur;
            int to_index = parent[cur].second;

            // edge (from, to)
            edge& forward = adjList[from][to_index];
            edge& reverse = adjList[to][forward.rev_index];

            // forward.capacity -= bottleneck; // if it was flow then += 
            // reverse.capacity += bottleneck;

            // actually bottleneck is 1 always

            forward.capacity ^= 1;
            reverse.capacity ^= 1;

            // I always forget this line
            cur = from;
        }

        fill(all(parent), make_pair(-1, -1));
    }

    cout << maxFlow;

    return 0;
}