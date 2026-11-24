
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;

        for (int i = 0; i < n; i++) {
            long long prod = 1;
            int g = 0, l = 1;

            for (int j = i; j < n; j++) {
                int x = nums[j];

                // Product can be huge, so check safely
                if (prod > 1e18 / x) {
                    break;
                }

                prod *= x;
                g = gcd(g, x);
                l = lcm(l, x);

                if (prod == 1LL * g * l) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};
