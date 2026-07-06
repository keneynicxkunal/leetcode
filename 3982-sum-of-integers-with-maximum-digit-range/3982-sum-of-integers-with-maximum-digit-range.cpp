class Solution {
public:
    int digitRange(int num) {
        int mn = 9, mx = 0;

        while (num > 0) {
            int d = num % 10;
            mn = min(mn, d);
            mx = max(mx, d);
            num /= 10;
        }

        return mx - mn;
    }

    int maxDigitRange(vector<int>& nums) {
        int maxRange = -1;
        int sum = 0;

        for (int num : nums) {
            maxRange = max(maxRange, digitRange(num));
        }

        for (int num : nums) {
            if (digitRange(num) == maxRange) {
                sum += num;
            }
        }

        return sum;
    }
};