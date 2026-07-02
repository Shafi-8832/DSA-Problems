class Solution {
public:
    vector<int> parent, group_size;

    int find(int i) {
        if (parent[i] != i) return parent[i] = find(parent[i]); // common mistake, people write find(i) again, causing an infinite loop.
        return i;
    }

    bool unite(int a, int b) {
        int parent_i = find(a);
        int parent_j = find(b);

        if (parent_i == parent_j) return false;

        if (group_size[parent_j] > group_size[parent_i]) {
            swap(parent_i, parent_j); // parent_i always holds larger
        }

        parent[parent_j] = parent_i;
        group_size[parent_i] += group_size[parent_j]; // notice size[parent_j] isn't updated! outdated value!

        return true;
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        // generate all edges, put them in a vector and sort it
        int n = points.size();
        parent.resize(n + 1);
        group_size.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);

        vector<tuple<int, int, int>> edges;
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {

                int x1 = points[i][0];
                int y1 = points[i][1];

                int x2 = points[j][0];
                int y2 = points[j][1];

                int w = abs(x1 - x2) + abs(y1 - y2);
                
                edges.push_back({w, i, j});
            }
        }

        sort(edges.begin(), edges.end());
        
        int mst_weight = 0;
        int edges_taken = 0;
        for (auto& e : edges) {
            if (unite( get<1>(e), get<2>(e) )) {
                mst_weight += get<0>(e);
                edges_taken++;
            }
            if (edges_taken == n-1) break;
        }

        return mst_weight;
    }
};