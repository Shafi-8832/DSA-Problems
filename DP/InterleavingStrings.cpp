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

    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    vector<bitset<1001>> dp(s1.size() + 1);

    if (s1.size() + s2.size() != s3.size()) {
        cout << 0 << '\n';
        return 0;
    }

    dp[0][0] = true;

    for (int i=0; i<=s1.size(); i++) {
        for (int j=0; j<=s2.size(); j++) {
            if (i == 0 && j == 0) continue;

            if (i == 0) dp[0][j] = dp[0][j-1] && s2[j-1] == s3[j-1];

            else if (j == 0) dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1];

            else {
                // if (s1[i - 1] == s3[i+j - 1]) dp[i][j] = dp[i-1][j];
                // if (s2[j - 1] == s3[i+j - 1]) dp[i][j] = dp[i][j-1];

                bool pathFromS1 = s1[i - 1] == s3[i+j - 1] && dp[i-1][j];
                bool pathFromS2 = s2[j - 1] == s3[i+j - 1] && dp[i][j-1];

                dp[i][j] = pathFromS1 || pathFromS2;
            }
        }
    }

    cout << dp[s1.size()][s2.size()] << '\n';
    
    return 0;
}