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

    int n, W; cin >> n >> W;

    vector<int>v(n);
    for (auto &val : v) cin >> val;

    vector<int>wt(n);
    for (auto &w : wt) cin >> w;

    vector<int>dp(W + 1, 0);

    // dp[w] = solution for max weight w

    for (int i=0; i<n; i++) { // item picker --> left to right for unbounded Knapsack
        for (int w=wt[i]; w<=W; w++) {
            dp[w] = max(dp[w], dp[w-wt[i]] + v[i]);
        }
    }
    
    cout << dp[W] << '\n';
    
    for (int i=0; i<n; i++) { // item picker --> right to left for 0-1 Knapsack
        for (int w=wt[i]; w<=W; w++) {
            dp[w] = max(dp[w], dp[w-wt[i]] + v[i]);
        }
    }

    cout << dp[W] << '\n';


    return 0;
}