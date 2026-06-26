#include "bits/stdc++.h"

using namespace std;

#define MAX_NODES 1000

int main() {
    int n, m; cin >> n >> m;

    vector<vector<int>> adj_list(n, vector<int>());
    bitset<MAX_NODES> visited;
    bitset<MAX_NODES> pathVisited;

    vector<int> indegree(n, 0);

    for (int i=0; i<m; i++) {
        int a, b; cin >> a >> b; // a ----> b
        adj_list[a].push_back(b);
        indegree[b]++;
    }

    queue<int> q;

    for (int i=0; i<indegree.size(); i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << u << " "

        for (int v : adj_list[u]) {
            indegree[v]--; // mathematically deleting the edge u ----> v
            if (indegree[v] == 0) q.push(v);
        }
    }

    // NOTES : why a visited array is not needed in Kahns
// and more on visited array

// look, when the indegree drops to 0 of a node, we have technically/mathematically deleted the edges incoming to that node, from the graph.

// the thing is, the algorithm only pushes the children

// if a node hits 0 indegree, that just means, it is no longer a child of anyone!

// so it will never get pushed AGAIN!

// remember it is a directed graph, a--->b doesn't mean b--->a, right?? 


}