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


typedef struct {
    int start_time;
    int finish_time;
    int value;
} job;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;

    vector<job> jobs(N);
    for (auto &j : jobs) {
        cin >> j.start_time >> j.finish_time >> j.value;
    }

    sort(all(jobs));

    vector<int> dp(N);
    for (int i=1; i<N; i++) {
        auto it = upper_bound(jobs.begin(), jobs.begin() + i, jobs[i].start_time);
        int valid_index = it - jobs.begin() - 1;
        
        dp[i] = max(dp[i-1], dp[valid_index] + jobs[i].value);
    }

    cout << "Max Value : " << dp[N-1];

    // backtracking

    list<int> locations;

    for (int i=N-1; i>=1; ) {
        auto it = upper_bound(jobs.begin(), jobs.begin() + i, jobs[i].start_time);
        int valid_index = it - jobs.begin() - 1;
        
        if (dp[i] == dp[i-1]) i--;
        else {
            locations.push_front(i);
            i = valid_index;
        }
    }
    
    return 0;
}