#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        
        for (int k = 1; k <= n; ++k) {
            // k must be a divisor of n
            if (n % k != 0) continue;
            
            bool possible = true;
            int prev_max = -1;
            
            for (int j = 0; j < n / k; ++j) {
                int start = j * k;
                int end = start + k - 1;
                
                int drops = 0;
                int curr_min = nums[start];
                int curr_max = nums[start];
                
                // Check elements within the current block
                for (int i = start; i < end; ++i) {
                    if (nums[i] > nums[i+1]) {
                        drops++;
                    }
                    curr_min = min(curr_min, nums[i+1]);
                    curr_max = max(curr_max, nums[i+1]);
                }
                // Check wrap-around drop for cyclic rotation validity
                if (nums[end] > nums[start]) {
                    drops++;
                }
                
                // If there's more than 1 drop, it cannot be sorted via cyclic rotations
                if (drops > 1) {
                    possible = false;
                    break;
                }
                
                // Max of previous block must be <= Min of current block
                if (j > 0 && prev_max > curr_min) {
                    possible = false;
                    break;
                }
                
                prev_max = curr_max;
            }
            
            // If all blocks can be cyclically sorted and naturally follow each other
            if (possible) {
                ans += k;
            }
        }
        
        return ans;
    }
};