#include <vector>

using namespace std;

class Solution {
    long long MOD = 1e9 + 7;
    vector<vector<long long>> comb;

    long long dfs(vector<int>& nums) {
        int n = nums.size();
        // Base case: 0, 1, or 2 elements only have 1 valid BST ordering.
        if (n <= 2) {
            return 1;
        }

        vector<int> left, right;
        int root = nums[0];
        
        // Split elements into left and right subtrees based on the root
        for (int i = 1; i < n; ++i) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }

        // Recursively find the number of ways for left and right subtrees
        long long left_ways = dfs(left);
        long long right_ways = dfs(right);

        int L = left.size();
        
        // Ways to interleave left and right subtree arrays
        long long interleave_ways = comb[n - 1][L];

        // Total ways = (interleave_ways * left_ways * right_ways) % MOD
        return (((interleave_ways * left_ways) % MOD) * right_ways) % MOD;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        
        // Precompute combinations using Pascal's Triangle
        comb.assign(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            comb[i][0] = 1; // nC0 is always 1
            for (int j = 1; j <= i; ++j) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }

        // We subtract 1 to exclude the original array configuration
        return (dfs(nums) - 1 + MOD) % MOD;
    }
};