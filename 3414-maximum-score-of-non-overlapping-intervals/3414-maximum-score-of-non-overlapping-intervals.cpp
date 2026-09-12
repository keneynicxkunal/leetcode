#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> indices;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return lexicographical_compare(
            a.indices.begin(), a.indices.end(),
            b.indices.begin(), b.indices.end()
        );
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];
            return x[3] < y[3];
        });

        vector<long long> ends(n);

        for (int i = 0; i < n; i++)
            ends[i] = a[i][1];

        // prev[i] = number of intervals before i
        // having right < current left
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            prev[i] = lower_bound(
                ends.begin(),
                ends.begin() + i,
                a[i][0]
            ) - ends.begin();
        }

        /*
            dp[i][k] = best answer using first i intervals
                       and choosing at most k intervals.
        */
        vector<array<State, 5>> dp(n + 1);

        for (int i = 1; i <= n; i++) {

            // Don't choose current interval
            for (int k = 0; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
            }

            // Choose current interval
            for (int k = 1; k <= 4; k++) {

                State candidate = dp[prev[i - 1]][k - 1];

                candidate.score += a[i - 1][2];
                candidate.indices.push_back((int)a[i - 1][3]);

                // Indices must be sorted for lexicographical comparison
                sort(candidate.indices.begin(), candidate.indices.end());

                if (better(candidate, dp[i][k])) {
                    dp[i][k] = candidate;
                }
            }
        }

        return dp[n][4].indices;
    }
};