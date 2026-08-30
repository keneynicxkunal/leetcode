class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        // Find indices of minimum and maximum
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        // Put smaller index in first
        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        // Case 1: Remove both from front
        int fromFront = right + 1;

        // Case 2: Remove both from back
        int fromBack = n - left;

        // Case 3: Remove left from front and right from back
        int bothSides = (left + 1) + (n - right);

        return min({fromFront, fromBack, bothSides});
    }
};