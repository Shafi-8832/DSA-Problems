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

vector<pair<int, int>> dirs = {
    {1, 2},
    {1, -2},
    {2, 1},
    {2, -1},
    {-1, 2},
    {-1, -2},
    {-2, 1},
    {-2, -1}
};

int n, m;
vector<vector<int>> grid;
vector<vector<bool>> visited;
vector<vector<int>> dist; // n X m
vector<vector<int>> reachable_count;

bool isValid(int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= m) return false;

    if (visited[r][c]) return false;

    // if (grid[r][c] == '#') return false;

    return true;
}

void bfs(int start_r, int start_c) {
    queue<pair<int, int>> q;

    q.push({start_r, start_c});
    visited[start_r][start_c] = true;
    dist[start_r][start_c] = 0;
    

    while (!q.empty()) {
        // extract u
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        reachable_count[r][c]++;

        // process

        for (auto d : dirs) {
            int child_r = r + d.first;
            int child_c = c + d.second;

            if (isValid(child_r, child_c)) {
                visited[child_r][child_c] = true;

                dist[child_r][child_c] = dist[r][c] + 1;
                q.push({child_r, child_c});
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int k; 
    cin >> n >> k;
    m = n;

    grid.assign(n, vector<int>(m));
    visited.assign(n, vector<bool>(m, false));
    dist.assign(n, vector<int>(m, -1));
    reachable_count.assign(n, vector<int>(m, 0));
    
    vector<vector<int>> answer(n, vector<int>(n, 0));
    
    
    
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            if (grid[i][j] == 1) {
                bfs(i, j);
                
                // hard copy 
                for (int r=0; r<n; r++) {
                    for (int c=0; c<m; c++) {
                        if (dist[r][c] == -1) answer[r][c] = dist[r][c];
                        answer[r][c] += dist[r][c];
                    }
                }
                
                dist.assign(n, vector<int>(m, -1));
                visited.assign(n, vector<bool>(m, false));
            }
        }
    }
    
    
    int min_moves = -1;
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            if (reachable_count[i][j] == k && ) min_moves = min(min_moves, answer[i][j]);
  
            cout << answer[i][j] << " ";
        }
        cout << '\n';
    }
    cout << min_moves;

    return 0;
}
