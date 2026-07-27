class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {

        int m = dungeon.size();
        int n = dungeon[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Last Cell (Princess)
        dp[m-1][n-1] = max(1, 1 - dungeon[m-1][n-1]);

        // Last Column
        for(int i = m - 2; i >= 0; i--) {
            dp[i][n-1] = max(1, dp[i+1][n-1] - dungeon[i][n-1]);
        }

        // Last Row
        for(int j = n - 2; j >= 0; j--) {
            dp[m-1][j] = max(1, dp[m-1][j+1] - dungeon[m-1][j]);
        }

        // Remaining Cells
        for(int i = m - 2; i >= 0; i--) {
            for(int j = n - 2; j >= 0; j--) {

                int right = dp[i][j+1];
                int down = dp[i+1][j];

                int need = min(right, down) - dungeon[i][j];

                if(need <= 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = need;
            }
        }

        return dp[0][0];
    }
};