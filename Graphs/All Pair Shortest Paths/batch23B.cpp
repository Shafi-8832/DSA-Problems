#include<bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using tiii = tuple<int, int, int>;
using pll = pair<ll, ll>;
#define f(t, i, x, y) for (t (i)=(x); (i)<(y); (i)++)
#define fe(t, i, x, y) for (t (i)=(x); (i)<=(y); (i)++)

#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define intmin INT64_MIN
#define int long long
#define intmax __INT64_MAX__


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);    

    int n, m; cin >> n >> m;
    vector<vector<int>> dp(n, vector<int>(n, intmax));
    for (int i=0; i<n; i++) dp[i][i] = 0;

    for (int i=0; i<m; i++) {
        int a, b;
        int c;
        cin >> a >> b >> c;

        dp[a][b] = c;
        dp[b][a] = c;
    }

    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (dp[i][k] != intmax && dp[k][j] != intmax) {
                    dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
                }
            }
        }
    }
    int y, z; cin >> y >> z;
    int q; cin >> q;

    while (q--) {
        int a, b; cin >> a >> b;

        int answer = min(dp[a][y] + dp[y][b],
                         dp[a][z] + dp[z][b]);

        cout << answer << '\n';
    }
    return 0;
}