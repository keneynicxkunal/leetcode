class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));

        // word1 -> empty string
        for (int i = 0; i <= n; i++) {
            dp[i][0] = i;
        }

        // empty string -> word2
        for (int j = 0; j <= m; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {

                if (word1[i - 1] == word2[j - 1]) {
                    // Same character, no operation needed
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    // Replace, Delete, Insert
                    dp[i][j] = 1 + min({
                        dp[i - 1][j],     // Delete
                        dp[i][j - 1],     // Insert
                        dp[i - 1][j - 1]  // Replace
                    });
                }
            }
        }

        return dp[n][m];
    }
};