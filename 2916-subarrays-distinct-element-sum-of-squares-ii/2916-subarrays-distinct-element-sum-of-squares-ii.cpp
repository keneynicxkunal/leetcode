#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
    
    struct Node {
        long long sum1 = 0;
        long long sum2 = 0;
        long long lazy = 0;
    };
    
    vector<Node> tree;
    
    void pushDown(int node, int start, int end) {
        if (tree[node].lazy != 0) {
            long long x = tree[node].lazy;
            int mid = start + (end - start) / 2;
            
            long long len_left = mid - start + 1;
            long long len_right = end - mid;
            
            // Update left child
            tree[2 * node].sum2 = (tree[2 * node].sum2 + 2 * x * tree[2 * node].sum1 + x * x % MOD * len_left) % MOD;
            tree[2 * node].sum1 = (tree[2 * node].sum1 + x * len_left) % MOD;
            tree[2 * node].lazy = (tree[2 * node].lazy + x) % MOD;
            
            // Update right child
            tree[2 * node + 1].sum2 = (tree[2 * node + 1].sum2 + 2 * x * tree[2 * node + 1].sum1 + x * x % MOD * len_right) % MOD;
            tree[2 * node + 1].sum1 = (tree[2 * node + 1].sum1 + x * len_right) % MOD;
            tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy + x) % MOD;
            
            tree[node].lazy = 0;
        }
    }
    
    void update(int node, int start, int end, int l, int r, long long val) {
        if (start > r || end < l) return;
        
        if (start >= l && end <= r) {
            long long len = end - start + 1;
            tree[node].sum2 = (tree[node].sum2 + 2 * val * tree[node].sum1 + val * val % MOD * len) % MOD;
            tree[node].sum1 = (tree[node].sum1 + val * len) % MOD;
            tree[node].lazy = (tree[node].lazy + val) % MOD;
            return;
        }
        
        pushDown(node, start, end);
        
        int mid = start + (end - start) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        
        tree[node].sum1 = (tree[2 * node].sum1 + tree[2 * node + 1].sum1) % MOD;
        tree[node].sum2 = (tree[2 * node].sum2 + tree[2 * node + 1].sum2) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n + 1, Node());
        
        unordered_map<int, int> last_pos;
        long long total_sum = 0;
        
        for (int i = 0; i < n; i++) {
            int start_idx = 1; 
            if (last_pos.count(nums[i])) {
                start_idx = last_pos[nums[i]] + 1; // 1-based indexing for Segment Tree
            }
            
            // Add 1 to the range of valid starting points for current element
            update(1, 1, n, start_idx, i + 1, 1);
            
            // tree[1].sum2 contains the sum of squares of distinct counts for all subarrays ending at index i
            total_sum = (total_sum + tree[1].sum2) % MOD;
            
            last_pos[nums[i]] = i + 1; // Store 1-based index
        }
        
        return total_sum;
    }
};