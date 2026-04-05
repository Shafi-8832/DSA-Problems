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


int n, m; 
vector<vector<char>> grid;
vector<vector<bool>> visited;

vector<pair<int, int>> dirs = {
    {-1, 0}, // up
    {1, 0}, // down
    {0, -1}, // left
    {0, 1} // right
};

bool isValid(int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= m) return false;

    if (visited[r][c]) return false;

    if (grid[r][c] == '#') return false;

    return true;
}

void dfs(int r, int c) {
    visited[r][c] = true;

    // do work
    // pasVisited[r][c] = true;
    // current_component_size++;
    // area++;

    for (auto d : dirs) {
        int child_r = r + d.first;
        int child_c = c + d.second;

        if (isValid(child_r, child_c)) dfs(child_r, child_c);
    }

}

void bfs(int start_r, int start_c) {
    queue<pair<int, int>> q;

    q.push({start_r, start_c});
    visited[start_r][start_c] = true;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        // process

        for (auto d : dirs) {
            int child_r = r + d.first;
            int child_c = c + d.second;

            if (isValid(child_r, child_c)) {
                visited[child_r][child_c] = true;

                // dist[child_r][child_c] = dist[child_r][child_c] + 1;
                q.push({child_r, child_c});
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    grid.assign(n, vector<char>(m));
    visited.assign(n, vector<bool>(m, false));
    
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int isLands = 0;
    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (grid[i][j] != '#' && !visited[i][j]) {
                isLands++;
                dfs(i, j); // or bfs(i, j);
            }
        }
    }

    int ans = 0;

    cout << ans << '\n';

    return 0;
}