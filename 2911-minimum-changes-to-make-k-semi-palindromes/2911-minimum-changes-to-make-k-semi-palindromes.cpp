#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        
        // 1. Precompute proper divisors for all lengths from 2 to n
        vector<vector<int>> divisors(n + 1);
        for (int len = 2; len <= n; ++len) {
            for (int d = 1; d < len; ++d) {
                if (len % d == 0) {
                    divisors[len].push_back(d);
                }
            }
        }
        
        // 2. Precompute minimum changes to make s[i..j] a semi-palindrome
        const int INF = 1e9;
        vector<vector<int>> cost(n, vector<int>(n, INF));
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                int min_changes = INF;
                
                for (int d : divisors[len]) {
                    int changes = 0;
                    // Check each of the 'd' arithmetic progression groups
                    for (int offset = 0; offset < d; ++offset) {
                        int left = i + offset;
                        int right = j - (d - 1 - offset);
                        while (left < right) {
                            if (s[left] != s[right]) {
                                ++changes;
                            }
                            left += d;
                            right -= d;
                        }
                    }
                    min_changes = min(min_changes, changes);
                }
                cost[i][j] = min_changes;
            }
        }
        
        // 3. DP to partition s[0..i-1] into p semi-palindromes
        // dp[p][i] = min changes for prefix of length i with p partitions
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;
        
        for (int p = 1; p <= k; ++p) {
            // Each partition needs length >= 2, so prefix length i >= 2*p
            // Remaining (k - p) partitions need at least 2*(k - p) characters
            for (int i = 2 * p; i <= n - 2 * (k - p); ++i) {
                // Previous prefix length m must be at least 2*(p - 1)
                // and last substring s[m..i-1] must have length >= 2 (m <= i - 2)
                for (int m = 2 * (p - 1); m <= i - 2; ++m) {
                    if (dp[p - 1][m] != INF) {
                        dp[p][i] = min(dp[p][i], dp[p - 1][m] + cost[m][i - 1]);
                    }
                }
            }
        }
        
        return dp[k][n];
    }
};