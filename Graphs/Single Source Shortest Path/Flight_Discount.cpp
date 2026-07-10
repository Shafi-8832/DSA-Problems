#include <bits/stdc++.h>

using namespace std;
#define int long long
#define INF INT64_MAX

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, e;
    cin >> n >> e;

    // vertices 1 to n

    vector<vector< pair<int, int> >> adj_list(n + 1, vector< pair<int, int> >());
    vector<vector<int>> d(n + 1, vector<int>(2, INF)); //

    for (int i=0; i<e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({w, v});
    }

    priority_queue<tuple<long long, int, int>, 
                vector<tuple<long long, int, int>>, 
                greater<tuple<long long, int, int>>> pq; // {destination, source, coupon_used}

    d[1][1] = INF; // *** ei value ta koi lagbe?

    d[1][0] = 0;

    pq.push({0, 1, 0});

    while (!pq.empty()) {
        auto [dist, u, coupon_used] = pq.top();
        // final, if coupon used = 1, then it is optimal to use coupon in the path s to u 

        // somewhere along the path
        pq.pop();

        // LAZY deletion
        if (dist > d[u][coupon_used]) continue;

        for (auto& [w, v] : adj_list[u]) {
            if (coupon_used) {
                if (d[u][1] != INF && d[v][1] > d[u][1] + w) {
                    d[v][1] = d[u][1] + w;
                    pq.push({d[v][1], v, 1});
                }
            }
            else {
                if (d[u][0] != INF) {
                    if (d[v][0] > d[u][0] + w) {
                        d[v][0] = d[u][0] + w;
                        pq.push({d[v][0], v, 0});
                    }
                    if (d[v][1] > d[u][0] + w/2) {
                        d[v][1] = d[u][0] + w/2;
                        pq.push({d[v][1], v, 1});
                    }
                }
            }
        }
    }

    cout << d[n][1] << '\n';

    // LAZY deletion is ABSOLUTELY IMPORTANT

    /*
    When you find a better path to node V, you push {new_distance, V} into the Priority Queue. 
    But the old, worse distance is still sitting in the queue! 
    C++ priority queues do not have an update function.
    When that old, worse version of V eventually rises to the top and pops out, you must ignore it.
    That is exactly what this line does:
    if (d > dist[u]) continue;
    If you forget this line, you process the node anyway and send out a "bad shockwave" of wasted work, leading straight to a Time Limit Exceeded (TLE) verdict.
    */
    return 0;
}
/*
State-Space Graph

By adding that coupon_used boolean, 
you didn't just change a variable—
you physically duplicated the graph into two identical parallel layers floating on top of each other.

d[i][1] = somewhere along the journey

d[i][1] & d[i][0] are the same graph up and down, the same edges, the same vertices, just one edge has w/2 *****

*/
