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
    vector<vector<int>> dp_org(n, vector<int>(n, intmax));
    vector<vector<int>> dp_dis(n, vector<int>(n, intmax));
    for (int i=0; i<n; i++) dp_org[i][i] = dp_dis[i][i] = 0;

    for (int i=0; i<m; i++) {
        int a, b;
        int c;
        cin >> a >> b >> c;

        dp_org[a][b] = c;
        dp_dis[a][b] = c - 1;
    }

    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (dp_org[i][k] != intmax && dp_org[k][j] != intmax) {
                    dp_org[i][j] = min(dp_org[i][k] + dp_org[k][j], dp_org[i][j]);
                }

                if (dp_dis[i][k] != intmax && dp_dis[k][j] != intmax) {
                    dp_dis[i][j] = min(dp_dis[i][k] + dp_dis[k][j], dp_dis[i][j]);
                }
            }
        }
    }

    int V; cin >> V;
    
    int q; cin >> q;

    while (q--) {
        int a, b; cin >> a >> b;

        //suppose : A ---- V ----- B (cost : 12, edges : 5) and A ----------- B. (cost : 10, edges : 5) two paths
        // if you run FW, then try to apply discount, look what happens
        // FW will pick up the cost 10 and put it in dp[A][B] = 10
        // it doesn't know that there is another path 12
        // here is the problem
        // path 1 has V in it, so discount = 5 * 1 so actually cost = 12 - 5 = 7! that's better than 10! but FW has no idea of 12 anymore
        // it has permanently picked up 10


        int answer = min(dp_org[a][b],
                         dp_dis[a][V] + dp_dis[V][b]);

        cout << answer << '\n';
    }
    return 0;
}