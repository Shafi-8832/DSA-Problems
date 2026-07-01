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


bool hasCycle = false;

bitset<26> visited;

void dfs(int source, vector<vector<int>>& adj_list) {
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
    
    vector<set<int>> adj_list(26, set<int>());
    // vector<int> indegree(26, 0);
    vector<bool> pathVisited(26, false);
    
    int n; cin >> n;
    for (int i=0; i<n; i++) {
        string s; cin >> s;
        for (int j=0; j<s.size()-1; j++) {
            adj_list[s[j] - 'A'].push_back(s[j+1] - 'A');
            
        }
    }

    for (int i=0; i<n; i++) {
        if (!visited[i]) dfs(i);
    }

    if (hasCycle) {
        cout << -1;
        return 0;
    }

    while (!topoSort.empty()) {
        cout << topoSort.top() << " ";
        topoSort.pop();
    }


    return 0;
}