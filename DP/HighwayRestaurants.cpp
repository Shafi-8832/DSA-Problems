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

    int N, K; cin >> N >> K;
    vector<int> m(N);
    for (auto &d : m) cin >> d;
    vector<int> p(N);
    for (auto &r : p) cin >> r;

    vector<int> dp(N);
    dp[0] = p[0];
    
    
    for (int i=1; i<N; i++) {
        int safe_distance_from_dhaka = m[i] - K;
        
        auto it = upper_bound(m.begin(), m.begin() + i, safe_distance_from_dhaka);
        
        int valid_index = it - m.begin() - 1;

        // big bug fix : valid index can be -1 if it == m.begin()
        int past_profit = (valid_index < 0) ? 0 : dp[valid_index];
        
        dp[i] = max(dp[i-1], past_profit + p[i]);
    }
    
    cout << "Max Profit : " << dp[N-1] << '\n';
    
    list<int> locations;
    // backtracking
    
    for (int i=N-1; i>=0; ) {
        if (i == 0) {
            locations.push_front(i);
            break;
        }

        int safe_distance = m[i] - K;
        auto it = upper_bound(m.begin(), m.begin() + i, safe_distance);
        int valid_index = it - m.begin() - 1;


        if (dp[i] == dp[i-1]) i--; // interrogate i-1, as we left i;
        else {
            locations.push_front(i);
            i = valid_index;
        }

    }
    
    cout << "Locations : ";
    for (auto &it : locations) cout << it << " ";


    return 0;
}