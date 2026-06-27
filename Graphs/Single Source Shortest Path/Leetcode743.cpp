class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector< pair<int, int> >> adj_list(n + 1);
        for (auto& t : times) {
            adj_list[t[0]].push_back({t[2], t[1]});
        }

        vector<int> d(n + 1, 1e9);
        d[k] = 0;

        set<pair<int, int>> pq;

        pq.insert({0, k});

        while (!pq.empty()) {
            int dist = pq.begin()->first;
            int u = pq.begin()->second;
            pq.erase(pq.begin()); // *** ETA NA DEWAR KARONE infinite loop e portesilo TLE

            // if (dist > d[u]) continue; // lazy deletion

            for (auto& [w, v] : adj_list[u]) {
                int old_dist = d[v];
                if (d[u] != 1e9 && d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pq.erase({old_dist, v});
                    pq.insert({d[v], v});
                }
            }
        }

        int max_dist = 0;
        for (int i=1; i<=n; i++) {
            if (d[i] == 1e9) return -1;
            max_dist = max(max_dist, d[i]);
        }

        return max_dist;
    }
};