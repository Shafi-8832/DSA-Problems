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

    int n, m, k, x; cin >> n >> m >> k >> x;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, intmax));
    vector<vector<int>> next(n + 1, vector<int>(n + 1, -1));
    for (int i=1; i<=n; i++) dp[i][i] = 0, next[i][i] = i;

    vector<int> city(k);
    for (int i=0; i<k; i++) cin >> city[i]; 
    
    vector<int> rate(k);
    for (int i=0; i<k; i++) cin >> rate[i];

    for (int i=0; i<m; i++) {
        int a, b;
        int c;
        cin >> a >> b >> c;

        dp[a][b] = c;
        dp[b][a] = c;
        next[a][b] = b;
        next[b][a] = a; 
    }

    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (dp[i][k] != intmax && dp[k][j] != intmax) {
                    dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
                    next[i][j] = next[i][k];
                    // next[j][i] = next[j][k]; // dui line i lekhar lage na, symmetric ek line likhlei hobe
                }
            }
        }
    }

    int min_cost = 0;
    int best_city = -1;
    int best_city_max_time = -1;

    for (int target_city = 1; target_city <= n; target_city++) {

        bool valid_city = true;

        int current_city_cost = 0;
        int current_city_max_time = 0;

        for (int lord = 0; lord < k; lord++) {
            int lord_city = city[lord];
            int time = dp[lord_city][target_city];

            if (time == intmax || time > x) {
                valid_city = false;
                break;
            }

            current_city_cost += (time) * rate[lord];

            current_city_max_time = max(current_city_max_time, time);
        }

        if (valid_city && min_cost > current_city_cost) {
            min_cost = current_city_cost;
            best_city_max_time = current_city_max_time;
            best_city = target_city;
        }
    }

    if (best_city == -1) {
        cout << "No meeting\n";
        return 0;
    }
    cout << best_city << " " << min_cost << " " << best_city_max_time << '\n';

    for (int lord = 0; lord < k; lord++) {
        int current_lord_city = city[lord];
        int this_lords_cost = rate[lord] * dp[current_lord_city][best_city];

        while (current_lord_city != best_city) {
            cout << current_lord_city << " -> ";
            current_lord_city = next[current_lord_city][best_city];
        }
        cout << best_city;
        cout << " " << this_lords_cost << '\n';
    }


    return 0;
}