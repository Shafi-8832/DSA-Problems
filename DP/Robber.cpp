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

    int N, MaxWeight; cin >> N >> MaxWeight;

    vector<int> v(N);
    for (auto &val : v) cin >> val;

    vector<int> wt(N);
    for (auto &weight : wt) cin >> weight;

    vector<vector<int>> dp(N, vector<int>(MaxWeight + 1, 0));

    // initialize house 0
    for (int w=0; w <= MaxWeight; w++) {
        dp[0][w] = (wt[0] > w) ? 0 : v[0];
    }
    
    // initialize houes 1
    for (int w=0; w <= MaxWeight; w++) {
        dp[1][w] = max(dp[0][w], (wt[1] > w) ? 0 : v[1]);
        // another way 
        // dp[1][w] = (wt[1] <= w) ? max(v[1], dp[0][w]) : dp[0][w];

        // first check whether you can actually rob or not
        // then you have 2 options , rob it (v[1] gained, can't rob house 0)

        // leave it --> same as before dp[0][w (doesn't change as we didn't rob it) ]

    }

    // main loop
    // lower rows down the grid
    for (int i = 2; i < N; i++) {
        for (int w = 0; w <= MaxWeight; w++) {
            
            int previousIncome = dp[i-2][w - wt[i]]; // can't have robbed immediate previous house

            int thisHouse = (wt[i] <= w) ? v[i] : 0; // gotta first check whether I can actually rob it or not

            int robIt = previousIncome + thisHouse;

            int leaveIt = dp[i-1][w];

            dp[i][w] = max(robIt, leaveIt);
        }
    }

    cout << dp[N-1][MaxWeight] << '\n';

    /* tc 1
    4 50
    60 100 120 100
    10 20 30 20
    */

    /* tc 2
    5 50
    60 120 80 100 70
    10 20 30 20 10
    */

    return 0;
}