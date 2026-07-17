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

    vector<pii> army_plan(n);
    for (int i=0; i<n; i++) {
        cin >> army_plan[i].first;
    }
    for (int i=0; i<n; i++) {
        cin >> army_plan[i].second;
    }


    for (int i=0; i<m; i++) {
        int a, b;
        int c;
        cin >> a >> b >> c;

        dp[a][b] = c;
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

    multiset<int, greater<int>> distances;

    for (int i=0; i<n; i++) {
        int d = dp[army_plan[i].first][army_plan[i].second];
        if (d != intmax) distances.insert(d);

    }

    int mult = 1;
    int sum = 0;
    int c = 0;

    for (auto& d : distances) {
        c++;
        sum += mult * d;
        if (c == k) {mult = mult << 1; c=0;}
    }

    cout << sum;


    return 0;
}