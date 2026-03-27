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

bool compareFinish(const job &a, const job &b) {
    return a.finish_time < b.finish_time;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;

    vector<job> jobs(N);
    for (auto &j : jobs) {
        cin >> j.start_time >> j.finish_time >> j.value;
    }

    sort(all(jobs), compareFinish);

    vector<int> dp(N);
    dp[0] = jobs[0].value; // BASE CASE add korte vule gesi


    vector<int> finish_times(N);
    for (int i=0; i<N; i++) finish_times[i] = jobs[i].finish_time;


    for (int i=1; i<N; i++) {
        auto it = upper_bound(finish_times.begin(), finish_times.begin() + i, jobs[i].start_time);
        int valid_index = it - finish_times.begin() - 1;

        int past_profit = (valid_index < 0) ? 0 : dp[valid_index];
        
        dp[i] = max(dp[i-1], past_profit + jobs[i].value);
    }

    cout << "Max Value : " << dp[N-1];



    // backtracking

    list<int> job_indices;

    for (int i=N-1; i>=0; ) {
        if (i == 0) {
            job_indices.push_front(i);
            break;
        }

        auto it = upper_bound(finish_times.begin(), finish_times.begin() + i, jobs[i].start_time);
        int valid_index = it - finish_times.begin() - 1;
        
        if (dp[i] == dp[i-1]) i--;
        else {
            job_indices.push_front(i);
            i = valid_index;
        }
    }
    
    return 0;
}