class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // suffix[i] = sum of piles[i ... n-1]
        vector<int> suffix(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // dp[i][M] = maximum stones current player can get
        // starting from index i with current M
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Process from the end towards the beginning
        for (int i = n - 1; i >= 0; i--) {
            for (int M = 1; M <= n; M++) {

                // Can take all remaining piles
                if (i + 2 * M >= n) {
                    dp[i][M] = suffix[i];
                    continue;
                }

                int best = 0;

                // Try taking X piles, where 1 <= X <= 2*M
                for (int X = 1; X <= 2 * M && i + X <= n; X++) {

                    // Stones we take now
                    int current = suffix[i] - suffix[i + X];

                    // Opponent gets dp[i+X][max(M,X)]
                    // We want to minimize opponent's stones
                    int opponent = dp[i + X][max(M, X)];

                    best = max(best, current + (suffix[i + X] - opponent));
                }

                dp[i][M] = best;
            }
        }

        return dp[0][1];
    }
};