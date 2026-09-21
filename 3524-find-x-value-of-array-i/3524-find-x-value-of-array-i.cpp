class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // dp[r] = number of subarrays ending at the
        // previous index whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            int a = num % k;

            vector<long long> newDp(k, 0);

            // Start a new subarray: [num]
            newDp[a]++;

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * a) % k;
                newDp[newRemainder] += dp[r];
            }

            // Add all subarrays ending at current position
            for (int r = 0; r < k; r++) {
                ans[r] += newDp[r];
            }

            dp = newDp;
        }

        return ans;
    }
};