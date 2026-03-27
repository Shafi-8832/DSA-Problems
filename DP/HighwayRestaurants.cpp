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
        
        dp[i] = max(dp[i-1], dp[valid_index] + p[i]);
    }
    
    cout << "Max Profit : " << dp[N-1] << '\n';
    
    list<int> locations;
    // backtracking
    
    for (int i=N-1; i>=1; ) {
        int safe_distance = m[i] - K;
        auto it = upper_bound(m.begin(), m.begin() + i, safe_distance);
        int valid_index = it - m.begin() - 1;
        
        if (dp[i-1] < dp[valid_index] + p[i]) {
            // built the restaurant exactly here (at index i)
            locations.push_front(i);
            i = valid_index; // back off
        }
        else i--; // interrogate i-1
    }
    
    cout << "Locations : ";
    for (auto &it : locations) cout << it << " ";


    return 0;
}