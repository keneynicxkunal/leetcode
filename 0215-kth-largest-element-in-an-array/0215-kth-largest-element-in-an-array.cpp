class Solution {
public:
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[right];
        int i = left;

        for (int j = left; j < right; j++) {
            if (nums[j] > pivot) { // For kth largest
                swap(nums[i], nums[j]);
                i++;
            }
        }

        swap(nums[i], nums[right]);
        return i;
    }

    int quickSelect(vector<int>& nums, int left, int right, int k) {
        int pivotIndex = partition(nums, left, right);

        if (pivotIndex == k)
            return nums[pivotIndex];
        else if (pivotIndex < k)
            return quickSelect(nums, pivotIndex + 1, right, k);
        else
            return quickSelect(nums, left, pivotIndex - 1, k);
    }

    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size() - 1, k - 1);
    }
};