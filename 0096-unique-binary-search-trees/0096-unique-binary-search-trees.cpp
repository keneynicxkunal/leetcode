class Solution {
public:
    int numTrees(int n) {
        vector<long long> dp(n + 1, 0);

        // Empty tree
        dp[0] = 1;

        // One node
        dp[1] = 1;

        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                int left = root - 1;
                int right = nodes - root;

                dp[nodes] += dp[left] * dp[right];
            }
        }

        return dp[n];
    }
};