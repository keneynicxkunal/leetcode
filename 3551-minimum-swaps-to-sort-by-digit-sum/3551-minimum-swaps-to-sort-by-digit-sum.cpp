
class Solution {
public:
    int digitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        vector<pair<int, int>> arr;

        // Store {digit sum, number}
        for (int x : nums) {
            arr.push_back({digitSum(x), x});
        }

        // Sort by digit sum, then by number
        sort(arr.begin(), arr.end());

        // Map each number to its original index
        unordered_map<int, int> pos;
        for (int i = 0; i < n; i++) {
            pos[nums[i]] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        // Count cycles
        for (int i = 0; i < n; i++) {
            if (visited[i] || pos[arr[i].second] == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;

                // Find where the current sorted element originally existed
                j = pos[arr[j].second];
                cycleSize++;
            }

            if (cycleSize > 1) {
                swaps += cycleSize - 1;
            }
        }

        return swaps;
    }
};
