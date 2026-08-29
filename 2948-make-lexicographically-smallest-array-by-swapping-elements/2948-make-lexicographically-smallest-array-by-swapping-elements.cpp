class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            a.push_back({nums[i], i});
        }

        // Sort by value
        sort(a.begin(), a.end());

        vector<int> ans(n);

        int start = 0;

        while (start < n) {
            int end = start;

            // Find one connected component
            while (end + 1 < n &&
                   a[end + 1].first - a[end].first <= limit) {
                end++;
            }

            // Values in this component are already sorted
            // because 'a' is sorted.
            //
            // Original indices are collected and sorted.
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(a[i].second);
            }

            sort(indices.begin(), indices.end());

            // Put smallest values at smallest indices
            for (int i = 0; i < (int)indices.size(); i++) {
                ans[indices[i]] = a[start + i].first;
            }

            start = end + 1;
        }

        return ans;
    }
};