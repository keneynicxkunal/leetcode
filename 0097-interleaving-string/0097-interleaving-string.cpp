class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size();
        int m = s2.size();

        // The lengths must match exactly.
        if (n + m != s3.size()) {
            return false;
        }

        /*
            dp[i][j] = whether s3[0 ... i+j-1] can be
                       formed using:
                       - first i characters of s1
                       - first j characters of s2
        */
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = true;

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {

                if (i == 0 && j == 0)
                    continue;

                int k = i + j - 1;

                // Take current character from s1
                if (i > 0 &&
                    dp[i - 1][j] &&
                    s1[i - 1] == s3[k]) {

                    dp[i][j] = true;
                }

                // Take current character from s2
                if (j > 0 &&
                    dp[i][j - 1] &&
                    s2[j - 1] == s3[k]) {

                    dp[i][j] = true;
                }
            }
        }

        return dp[n][m];
    }
};