class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int totalXor = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            totalXor ^= x;
            if (x != 0) {
                hasNonZero = true;
            }
        }

        // XOR of the entire array is non-zero
        if (totalXor != 0) {
            return nums.size();
        }

        // Total XOR is zero, but we have a non-zero element.
        // Remove that one element -> remaining XOR becomes non-zero.
        if (hasNonZero) {
            return nums.size() - 1;
        }

        // All elements are zero.
        return 0;
    }
};