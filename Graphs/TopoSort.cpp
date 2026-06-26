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


vector<vector<int>> adj_list;
vector<bool> visited;
vector<bool> pasVisited; // This array basically simulates the active nodes on a DFS traversal.
// we know DFS internally maintains a Stack. if a node is in the stack, then that is an ACTIVE node.

stack<int> topoSort; // This is completely a different stack, DON'T mix it with DFS's internal stack.
// 


bool hasCycle = false;

void dfs(int source) {
    visited[source] = true;
    pasVisited[source] = true; // ACTIVE **

    for (auto child : adj_list[source]) {
        if (!visited[child]) dfs(child);
        else if (pasVisited[child]) hasCycle = true;
    }

    pasVisited[source] = false; // popping out of the stack, so becoming INACTIVE node **
    topoSort.push(source); // the Deadends are to be Pushed in the stack
    // the dead ends have outdegree = 0.
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i=0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj_list[a].push_back(b);
    }

    while (!topoSort.empty()) {
        cout << topoSort.top() << " ";
        topoSort.pop();
    }

    // CRUX : Because a node is only pushed to the stack after all its children are pushed, 
    // it guarantees that when we pop from the stack later, the parent will always come before the child.

    // The parent will ALWAYS come before the child.
    // that means in our TopoSort Stack, we have parents stacking on top of children. the directed edges are pointing downwards in the stack

    // so when we pop from top, we are always choosing parents_courses to finish then the children_courses
    
    
    return 0;
}