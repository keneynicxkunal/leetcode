class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {
        vector<int> diff;
        int n = nums1.size();

        long long total = 0;

        for (int i = 0; i < n; i++) {
            int d = abs(nums1[i] - nums2[i]);
            diff.push_back(d);
            total += d;
        }

        long long k = (long long)k1 + k2;

        // If all differences can be eliminated
        if (total <= k) return 0;

        int low = 0, high = 100000;

        // Find the minimum maximum difference possible
        while (low < high) {
            int mid = low + (high - low) / 2;

            long long needed = 0;

            for (int d : diff) {
                if (d > mid) {
                    needed += d - mid;
                }
            }

            if (needed <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int limit = low;
        long long ans = 0;

        // Reduce all differences greater than limit
        for (int& d : diff) {
            if (d > limit) {
                k -= d - limit;
                d = limit;
            }
        }

        // Distribute remaining operations optimally
        // by reducing some differences equal to limit
        for (int& d : diff) {
            if (k > 0 && d == limit) {
                d--;
                k--;
            }

            ans += 1LL * d * d;
        }

        return ans;
    }
};