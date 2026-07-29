class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums;
        vector<int> fact(n);

        fact[0] = 1;
        for (int i = 1; i < n; i++)
            fact[i] = fact[i - 1] * i;

        for (int i = 1; i <= n; i++)
            nums.push_back(i);

        k--; // Convert to 0-based indexing

        string ans = "";

        for (int i = n; i >= 1; i--) {
            int index = k / fact[i - 1];
            ans += to_string(nums[index]);

            nums.erase(nums.begin() + index);

            k %= fact[i - 1];
        }

        return ans;
    }
};