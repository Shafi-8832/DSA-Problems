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

    string s; cin >> s;
    int length = s.size();

    vector<vector<int>> dp(length, vector<int>(length, 0)); // O(N^2)

    for (int i = 0; i < length; i++) dp[i][i] = 1; // O(N)

    // diagonally traversing the 2D array
    for (int len = 2; len <= length; len++) { // n(1-n)/2 times --> O(N^2)
        for (int l = 0, r = l + len - 1; r < length; r++, l++) {

            if (s[l] == s[r]) dp[l][r] = 2 + dp[l + 1][r - 1];
            else dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);

        }
    }
    
    // backtracking
    string answer = "";
    int l = 0, r = length - 1;
    while (l <= r) { // O(N/2)
        if (l == r) { // odd lengthed palindrome
            answer.push_back(s[l]);
            break;
        }

        if (s[l] == s[r]) {
            answer.push_back(s[l]);
            l++; r--;
        }
        else if (dp[l + 1][r] > dp[l][r - 1]) l++;
        else r--;
    }

    cout << dp[0][length - 1] << '\n';

    cout << answer;

    string t = answer;
    if (dp[0][length - 1] % 2 != 0) t.pop_back();

    reverse(all(t));
    cout << t;

    



    return 0;
}