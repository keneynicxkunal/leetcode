class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();

        // dp[i] = number of ways to decode first i characters
        vector<int> dp(n + 1, 0);

        dp[0] = 1;

        // First character
        if (s[0] != '0') {
            dp[1] = 1;
        }

        for (int i = 2; i <= n; i++) {

            // Take the current digit as a single character
            if (s[i - 1] != '0') {
                dp[i] += dp[i - 1];
            }

            // Take the last two digits together
            int num = (s[i - 2] - '0') * 10 +
                      (s[i - 1] - '0');

            if (num >= 10 && num <= 26) {
                dp[i] += dp[i - 2];
            }
        }

        return dp[n];
    }
};