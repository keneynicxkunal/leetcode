class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][0] = Ways entering from left (moving right)
        // dp[i][j][1] = Ways entering from above (moving down)

        vector<vector<vector<long long>>> dp(
            m, vector<vector<long long>>(n, vector<long long>(2, 0))
        );

        // Robot starts at (0, 0)
        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                long long right = dp[i][j][0];
                long long down = dp[i][j][1];

                if (grid[i][j] == 1) {

                    // Mirror:
                    // Entered while moving right -> reflect down
                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + right) % MOD;
                    }

                    // Entered while moving down -> reflect right
                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + down) % MOD;
                    }

                } else {

                    // Empty cell: robot can move right or down

                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + right + down) % MOD;
                    }

                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + right + down) % MOD;
                    }
                }
            }
        }

        // Destination is guaranteed to be empty
        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};