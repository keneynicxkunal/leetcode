class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Valid parentheses string ki length even honi chahiye
        if ((m + n - 1) % 2 != 0)
            return false;

        // dp[i][j] = possible balances at cell (i,j)
        vector<vector<unordered_set<int>>> dp(
            m, vector<unordered_set<int>>(n)
        );

        // Starting cell
        if (grid[0][0] == '(')
            dp[0][0].insert(1);
        else
            return false;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                // Current cell '(' hai toh +1
                // ')' hai toh -1
                int change = (grid[i][j] == '(') ? 1 : -1;

                // Upar se aa rahe hain
                if (i > 0) {
                    for (int balance : dp[i - 1][j]) {
                        int newBalance = balance + change;

                        // Balance negative nahi hona chahiye
                        if (newBalance >= 0) {
                            dp[i][j].insert(newBalance);
                        }
                    }
                }

                // Left se aa rahe hain
                if (j > 0) {
                    for (int balance : dp[i][j - 1]) {
                        int newBalance = balance + change;

                        if (newBalance >= 0) {
                            dp[i][j].insert(newBalance);
                        }
                    }
                }
            }
        }

        // End par balance 0 hona chahiye
        return dp[m - 1][n - 1].count(0);
    }
};