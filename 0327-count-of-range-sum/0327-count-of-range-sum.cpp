class Solution {
public:
    int mergeSort(vector<long long>& prefix, int left, int right, int lower, int upper) {
        if (right - left <= 1) return 0;

        int mid = left + (right - left) / 2;
        int count = mergeSort(prefix, left, mid, lower, upper) +
                    mergeSort(prefix, mid, right, lower, upper);

        int j = mid, k = mid;

        for (int i = left; i < mid; i++) {
            while (k < right && prefix[k] - prefix[i] < lower)
                k++;
            while (j < right && prefix[j] - prefix[i] <= upper)
                j++;
            count += j - k;
        }

        vector<long long> temp;
        int p1 = left, p2 = mid;

        while (p1 < mid && p2 < right) {
            if (prefix[p1] <= prefix[p2])
                temp.push_back(prefix[p1++]);
            else
                temp.push_back(prefix[p2++]);
        }

        while (p1 < mid)
            temp.push_back(prefix[p1++]);

        while (p2 < right)
            temp.push_back(prefix[p2++]);

        for (int i = 0; i < temp.size(); i++)
            prefix[left + i] = temp[i];

        return count;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();

        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];

        return mergeSort(prefix, 0, n + 1, lower, upper);
    }
};