class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size();
        int n = t.size();

        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= m; i++) {
            for (int j = min(i, n); j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];

                    // Prevent overflow
                    if (dp[j] > INT_MAX)
                        dp[j] = INT_MAX;
                }
            }
        }

        return (int)dp[n];
    }
};