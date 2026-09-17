class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        // best[i] = minimum length of a valid subarray
        // ending at or before index i
        vector<int> best(n, INT_MAX);

        int left = 0;
        long long sum = 0;
        int ans = INT_MAX;
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink window while sum is too large
            while (left <= right && sum > target) {
                sum -= arr[left];
                left++;
            }

            // If current window has sum == target
            if (sum == target) {
                int len = right - left + 1;

                // There must be a previous non-overlapping
                // subarray ending before 'left'
                if (left > 0 && best[left - 1] != INT_MAX) {
                    ans = min(ans, len + best[left - 1]);
                }

                // Keep the shortest valid subarray
                minLen = min(minLen, len);
            }

            // Carry forward the best answer up to this index
            if (right == 0)
                best[right] = minLen;
            else
                best[right] = min(best[right - 1], minLen);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};