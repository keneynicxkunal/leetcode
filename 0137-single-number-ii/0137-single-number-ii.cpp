class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;

        for (int bit = 0; bit < 32; bit++) {
            int count = 0;

            for (int num : nums) {
                if ((num >> bit) & 1)
                    count++;
            }

            if (count % 3)
                ans |= (1LL << bit);
        }

        return ans;
    }
};