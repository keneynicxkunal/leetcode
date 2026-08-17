#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // Prefix sum
        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        // dp[l][r] = maximum score for subarray [l...r]
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Length of interval
        for (int len = 2; len <= n; len++) {

            for (int l = 0; l + len - 1 < n; l++) {

                int r = l + len - 1;

                // Try every possible split
                for (int k = l; k < r; k++) {

                    long long leftSum =
                        prefix[k + 1] - prefix[l];

                    long long rightSum =
                        prefix[r + 1] - prefix[k + 1];

                    if (leftSum < rightSum) {

                        // Right side is discarded
                        dp[l][r] = max(
                            dp[l][r],
                            dp[l][k] + leftSum
                        );

                    } 
                    else if (leftSum > rightSum) {

                        // Left side is discarded
                        dp[l][r] = max(
                            dp[l][r],
                            dp[k + 1][r] + rightSum
                        );

                    } 
                    else {

                        // Equal sums: Alice chooses
                        dp[l][r] = max(
                            dp[l][r],
                            max(dp[l][k],
                                dp[k + 1][r]) + leftSum
                        );
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};