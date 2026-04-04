class Solution {
public:
    int numDistinct(string s, string t) {
        int N = s.size(), M = t.size();
        vector<vector<unsigned long long>> dp(N + 1, vector<unsigned long long>(M + 1, 0));

        for (int i=0; i<=N; i++) dp[i][0] = 1; // WATCH OUT!!  empty strings to be counted.

        for (int i=1; i<=N; i++) {
            for (int j=1; j<=M; j++) {
                if (s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }
                else dp[i][j] = dp[i-1][j];
            }
        }

        return dp[N][M];
    }
};
