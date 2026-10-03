class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();

        if (n == 0)
            return 0;

        vector<int> dp(n, 0);
        int ans = 0;

        for (int i = 1; i < n; i++) {

            // Case 1: current character is ')'
            if (s[i] == ')') {

                // Case: "()"
                if (s[i - 1] == '(') {
                    dp[i] = 2;

                    // Add the valid substring before "()"
                    if (i >= 2)
                        dp[i] += dp[i - 2];
                }

                // Case: "...))"
                else if (s[i - 1] == ')') {

                    // Find the matching '('
                    int j = i - dp[i - 1] - 1;

                    if (j >= 0 && s[j] == '(') {
                        dp[i] = dp[i - 1] + 2;

                        // Add valid substring before matching '('
                        if (j >= 1)
                            dp[i] += dp[j - 1];
                    }
                }
            }

            ans = max(ans, dp[i]);
        }

        return ans;
    }
};