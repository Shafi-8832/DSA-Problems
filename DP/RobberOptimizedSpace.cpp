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

    // optimization
    // ASK : when calculating the current DP state / solving the current subproblem
    // "How far back in Time does the Recurrence relation / formula forces me to look at?"
    // I need to look at i-1 and i-2 only to calculate i !
    // the rows far up ahead are not needed for i!
    // I can only keep 2 1D array and overwrite on them 
    // first iteration : 0 1
    // 2nd iteration : 1 2
    // 3rd iteration : 3 4


    int N, MaxWeight; cin >> N >> MaxWeight;

    vector<int> v(N);
    for (auto &val : v) cin >> val;

    vector<int> wt(N);
    for (auto &weight : wt) cin >> weight;

    vector<vector<int>> dp(2, vector<int>(MaxWeight + 1)); // 2 X MaxWeight

    for (int w = 0; w <= MaxWeight; w++) { // House No 0 precompute
        dp[0][w] = (wt[0] > w) ? 0 : v[0];
    }
    
    if (N == 1) {
        cout << dp[0][MaxWeight];
        return 0;
    }

    for (int w = 0; w <= MaxWeight; w++) { // House No 1 precompute
        dp[1][w] = max( dp[0][w], (wt[1] <= w) ? v[1] : 0 );
    }
    
    // For house no i >= 2, we only need 2 previous states i-1, i-2
    

    int HouseNo = 2;
    for ( ; HouseNo <= N-1; HouseNo++) {

        for (int w = MaxWeight ; w >= 0; w--) { // RIGHT TO LEFT
            int RobIt = 0;
            if (wt[HouseNo] <= w) { // Robbable?
                RobIt = v[HouseNo] + dp[ (HouseNo - 2)%2 ][w - wt[HouseNo]];
            }

            int leaveIt = dp[ (HouseNo - 1)%2 ][w];

            dp[HouseNo % 2][w] = max(leaveIt, RobIt);
        }
    }

    HouseNo = N-1;
    cout << dp[HouseNo % 2][MaxWeight];
    
    return 0;
}