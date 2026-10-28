class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        const int X = 1024;

        vector<bitset<X>> dp(m * n);

        dp[0][grid[0][0]] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    continue;

                int idx = i * n + j;
                int val = grid[i][j];

                for (int x = 0; x < X; x++) {
                    if (i > 0 && dp[(i - 1) * n + j][x])
                        dp[idx][x ^ val] = 1;

                    if (j > 0 && dp[i * n + j - 1][x])
                        dp[idx][x ^ val] = 1;
                }
            }
        }

        for (int x = 0; x < X; x++) {
            if (dp[m * n - 1][x])
                return x;
        }

        return 0;
    }
};