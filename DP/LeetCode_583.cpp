class Solution {
public:
    int minDistance(string word1, string word2) {
        int N = word1.size();
        int M = word2.size();

        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        // precompute base cases
        for (int i=1; i<=N; i++) dp[i][0] = i;
        for (int j=1; j<=M; j++) dp[0][j] = j;

        // fill the main dp table
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=M; j++) {
                // if the characters don't match, then you at current step, MUST perform a deletion
                // delete s[i-1] and grab dp[i-1][j]'s recipe and make them equal
                // delete t[j-1] and grab dp[i][j-1]'s recipe and make them equal
                //       1        +  whichever previous recipe gives you minimum deletions 
                if (word1[i-1] != word2[j-1]) dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
                else dp[i][j] = dp[i-1][j-1];
            }
        }

        // if 2 chars don't match, they can't BOTH be in LCS.
        // if 2 chars match, they MUST BOTH be in LCS.
        // as the last character.
        // 2 chars same iff they both be in LCS.
        return dp[N][M];
    }
};
