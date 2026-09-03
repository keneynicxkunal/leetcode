class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        // If the minimum is odd, we can make all elements odd.
        if (mn % 2 == 1)
            return true;

        // If minimum is even, all elements must already be even.
        for (int x : nums1) {
            if (x % 2 == 1)
                return false;
        }

        return true;
    }
};