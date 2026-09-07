class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;
        
        int n = s.size();
        vector<long long> dp(n + 1, 0);
        
        // dp[0] = 1 -> empty subsequence
        dp[0] = 1;
        
        // Last occurrence of each character (1-based index)
        vector<int> last(26, 0);
        
        for (int i = 1; i <= n; i++) {
            int c = s[i - 1] - 'a';
            
            // Double all existing subsequences
            dp[i] = (2 * dp[i - 1]) % MOD;
            
            // Remove duplicates caused by previous occurrence
            if (last[c] != 0) {
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
            }
            
            last[c] = i;
        }
        
        // Remove empty subsequence
        return (dp[n] - 1 + MOD) % MOD;
    }
};