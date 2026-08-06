class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        vector<int> arr(n + 2, 1);
        for (int i = 0; i < n; i++)
            arr[i + 1] = nums[i];

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for (int len = 1; len <= n; len++) {
            for (int left = 1; left <= n - len + 1; left++) {
                int right = left + len - 1;

                for (int k = left; k <= right; k++) {
                    dp[left][right] = max(
                        dp[left][right],
                        dp[left][k - 1] +
                        arr[left - 1] * arr[k] * arr[right + 1] +
                        dp[k + 1][right]
                    );
                }
            }
        }

        return dp[1][n];
    }
};