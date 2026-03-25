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


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string S, T; cin >> S >> T;
    int n = S.size(), m = T.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i=1; i<=n; i++) dp[i][0] = i; // delete i chars = i operations
    for (int j=1; j<=m; j++) dp[0][j] = j; // insert j chars = j operations

    dp[0][0] = 0; // trivial

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (S[i -1] == T[j -1]) {
                dp[i][j] = dp[i-1][j-1]; 
            }
            else {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }

    cout << dp[n][m] << '\n';
    
    return 0;
}