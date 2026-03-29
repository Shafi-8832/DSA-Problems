class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int N = s1.size();
        int M = s2.size();

        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        // precompute base cases
        for (int i=1; i<=N; i++) dp[i][0] = dp[i-1][0] + s1[i-1]; // first column (0th column)
        for (int j=1; j<=M; j++) dp[0][j] = dp[0][j-1] + s2[j-1]; // first row (0th row)

        // fill the main dp table
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=M; j++) {
                // if the chars don't match, you MUST throw away either one of the 2 last chars
                // which one do you throw? the one with lower ASCII number.
                if (s1[i-1] != s2[j-1]) {
                    dp[i][j] = min(dp[i-1][j] + s1[i-1],  dp[i][j-1] + s2[j-1]);
                }
                else dp[i][j] = dp[i-1][j-1]; // Greedy Choice Property: if the chars match don't delete!
            }
        }

        return dp[N][M];
    }
};
