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

    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, intmax));
    for (int i=1; i<=n; i++) dp[i][i] = 0;

    vector<int> cap(n + 1);
    for (int i=1; i<=n; i++) {
        cin >> cap[i];
    }


    for (int i=0; i<m; i++) {
        int a, b;
        int c;
        cin >> a >> b >> c;

        if (cap[a] != -1 && cap[b] != -1) dp[a][b] = c, dp[b][a] = c;
        // dp[b][a] = c;
    }

    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (dp[i][k] != intmax && dp[k][j] != intmax) {
                    dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
                }
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int u; cin >> u;
        // row u
        multiset<pii> d;
        for (int i=1; i<=n; i++) {
            if (dp[u][i] == intmax) continue;
            d.insert({dp[u][i], cap[i]});
        }
    
        int student_placed = 0;
        for (auto& t : d) {

            // suppose the closest lab is lab 3, cost = 4, capacity = 3
            // then the cost is going to get printed 3 times
            // 4 4 4 
            int cap = t.second;
            int cost = t.first;

            while (cap > 0 && student_placed < k) {
                cout << cost << " ";
                cap--;
                student_placed++;
            }
            if (student_placed == k) break;
            
        }
        while (student_placed < k) cout << -1 << " ", s++;
    }


    return 0;
}