class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;

        vector<vector<long long>> dp(n, vector<long long>(k + 1));

        // dp[i][j]:
        // number of ways to draw j segments using points [0 ... i]
        
        // 0 segments -> 1 way
        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
        }

        for (int j = 1; j <= k; j++) {
            long long prefix = 0;

            for (int i = 1; i < n; i++) {

                // Previous j-1 segments can end at any point
                // from 0 to i-1.
                prefix = (prefix + dp[i - 1][j - 1]) % MOD;

                // Don't start/end a segment at i
                dp[i][j] = dp[i - 1][j];

                // Create a segment whose right endpoint is i.
                dp[i][j] = (dp[i][j] + prefix) % MOD;
            }
        }

        return dp[n - 1][k];
    }
};