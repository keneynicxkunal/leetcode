#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;
        
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                idx = i;
                break;
            }
        }
        
        bool isAsc = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(i + 1) % n] != (nums[i] + 1) % n) {
                isAsc = false;
                break;
            }
        }
        
        bool isDesc = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(i + 1) % n] != (nums[i] - 1 + n) % n) {
                isDesc = false;
                break;
            }
        }
        
        int ans = 1e9; // Start with a very large value (infinity)
        
        // If the array is a cyclic shift of the sorted array [0, 1, 2, ..., n-1]
        if (isAsc) {
            ans = min(ans, idx);             // Just left rotate 'idx' times
            ans = min(ans, n - idx + 2);     // Or Reverse, Left Rotate (n - idx) times, Reverse
        }
        
        // If the array is a cyclic shift of the reverse sorted array [n-1, n-2, ..., 0]
        if (isDesc) {
            ans = min(ans, idx + 2);         // Left rotate 'idx' times, Left rotate 1 more, Reverse
            ans = min(ans, n - idx);         // Reverse (now ascending), Left rotate (n - idx) times
        }
        
        return ans == 1e9 ? -1 : ans;
    }
};