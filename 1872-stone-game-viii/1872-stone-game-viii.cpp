#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long stoneGameVIII(vector<int>& stones) {
        int n = stones.size();

        // Prefix sums
        vector<long long> P(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            P[i] = P[i - 1] + stones[i - 1];
        }

        const long long INF = (1LL << 60);

        vector<long long> alice(n + 1, -INF);
        vector<long long> bob(n + 1, INF);

        // When there is only one stone left, game is over.
        alice[n] = bob[n] = 0;

        // We need:
        // alice[i] = max(P[j] + bob[j]) for j > i
        // bob[i]   = min(-P[j] + alice[j]) for j > i
        //
        // Maintain suffix maximum/minimum.
        long long bestAlice = -INF;
        long long bestBob = INF;

        for (int i = n - 1; i >= 1; i--) {
            // j = i + 1 is now available
            bestAlice = max(bestAlice, P[i + 1] + bob[i + 1]);
            bestBob = min(bestBob, -P[i + 1] + alice[i + 1]);

            alice[i] = bestAlice;
            bob[i] = bestBob;
        }

        // Initially Alice must remove at least 2 stones.
        long long answer = -INF;

        for (int j = 2; j <= n; j++) {
            answer = max(answer, P[j] + bob[j]);
        }

        return answer;
    }
};