
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();

        // Next Greater Element
        vector<int> nxt(n);
        vector<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i]) {
                st.pop_back();
            }

            nxt[i] = st.empty() ? n : st.back();
            st.push_back(i);
        }

        // Prefix Sum
        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Binary Lifting
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> dp(LOG, vector<long long>(n + 1, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            dp[0][i] =
                1LL * nums[i] * (nxt[i] - i)
                - (pref[nxt[i]] - pref[i]);
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i <= n; i++) {
                int mid = up[j - 1][i];

                up[j][i] = up[j - 1][mid];

                dp[j][i] =
                    dp[j - 1][i] + dp[j - 1][mid];
            }
        }

        // Calculate operations needed for [l, r]
        auto getCost = [&](int l, int r) -> long long {
            long long cost = 0;
            int cur = l;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][cur] <= r + 1) {
                    cost += dp[j][cur];
                    cur = up[j][cur];
                }
            }

            if (cur <= r) {
                cost += 1LL * nums[cur] * (r - cur + 1)
                      - (pref[r + 1] - pref[cur]);
            }

            return cost;
        };

        // Binary Search for each right endpoint
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int low = 0, high = r;

            while (low < high) {
                int mid = low + (high - low) / 2;

                if (getCost(mid, r) <= k) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }

            ans += (r - low + 1);
        }

        return ans;
    }
};
