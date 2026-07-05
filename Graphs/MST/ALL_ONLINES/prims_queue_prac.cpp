int n, m; cin >> n >> m;
vector<vector<pii>> adj(n, vector<pii>());

for (int i=0; i<m; i++) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].pb({w, v});
    adj[v].pb({w, u});
}

priority_queue<tiii, vector<tiii>, greater<tiii>()> pq;
// {weight, origin ---> destination}

vector<bool> in_mst(n, false); // visited(n, false);
vector<pii> final_edges;

int mst = 0;
int edges_taken = 0, nodes_taken = 0;

pq.push({0, -1, 0}); // weight = 0 , node -1 to node 0;

bool possible = false;


while (!pq.empty()) {
    auto [w, u, v] = pq.top(); // u ----> v
    pq.pop(); // 

    if (in_mst[v]) continue; // then some other edge to this node V has been picked up earlier, so you can't take this, otherwise it would create a cycle

    int_mst[v] = true;
    mst += w;
    nodes_taken++;
    final_edges.pb({u, v});


    if (nodes_taken == n) {
        possible = true;
        break;
    }


    for (auto [w2, v2] : adj[v]) {
        if (in_mst[v2]) continue; // obviously a cycle
        pq.push({w2, v, v2});
    }
}