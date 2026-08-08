#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // positions[c] = all positions of character c in word1
        vector<vector<int>> positions(26);

        for (int i = 0; i < n; i++) {
            positions[word1[i] - 'a'].push_back(i);
        }

        /*
            exact[j] = latest possible index used for word2[j]
                      when word2[j..m-1] is matched exactly.

            exact[m] = n means empty suffix is possible.
            -1 means impossible.
        */
        vector<int> exact(m + 1, -1);
        exact[m] = n;

        int p = n - 1;

        for (int j = m - 1; j >= 0; j--) {
            while (p >= 0 && word1[p] != word2[j]) {
                p--;
            }

            if (p < 0) {
                break;
            }

            exact[j] = p;
            p--;
        }

        /*
            runStart[i] = beginning of the consecutive run
                         containing word1[i].

            Example:
            word1 = "aaabbc"
                   012345

            runStart = [0,0,0,3,3,5]
        */
        vector<int> runStart(n);

        for (int i = 0; i < n; i++) {
            if (i == 0 || word1[i] != word1[i - 1])
                runStart[i] = i;
            else
                runStart[i] = runStart[i - 1];
        }

        /*
            Find the latest position < bound whose character
            is different from target.

            O(1).
        */
        auto lastDifferent = [&](int bound, char target) -> int {
            if (bound <= 0)
                return -1;

            int i = bound - 1;

            if (word1[i] != target)
                return i;

            // word1[i] == target.
            // Skip the entire consecutive run of target.
            return runStart[i] - 1;
        };

        /*
            almost[j] = latest possible index used for word2[j]
                       when word2[j..m-1] can be matched with
                       at most ONE mismatch.

            almost[m] = n (empty suffix).
        */
        vector<int> almost(m + 1, -1);
        almost[m] = n;

        for (int j = m - 1; j >= 0; j--) {
            char target = word2[j];
            int best = -1;

            /*
                Case 1:
                word1[i] == word2[j]

                Then the mismatch, if any, can happen later.
            */
            if (almost[j + 1] != -1) {
                int bound = almost[j + 1];

                auto &v = positions[target - 'a'];

                auto it = lower_bound(v.begin(), v.end(), bound);

                if (it != v.begin()) {
                    --it;
                    best = max(best, *it);
                }
            }

            /*
                Case 2:
                word1[i] != word2[j]

                Then this position consumes our one mismatch,
                so the remaining suffix must match exactly.
            */
            if (exact[j + 1] != -1) {
                int candidate =
                    lastDifferent(exact[j + 1], target);

                best = max(best, candidate);
            }

            almost[j] = best;
        }

        /*
            Greedily construct the lexicographically smallest answer.

            For every position j, try the smallest possible index i.
        */
        vector<int> ans;

        int prev = -1;
        bool mismatchUsed = false;

        for (int j = 0; j < m; j++) {
            bool found = false;

            /*
                Need enough remaining positions.

                If we choose i for word2[j],
                there must be m-j-1 positions after i.
            */
            int maxIndex = n - (m - j);

            for (int i = prev + 1; i <= maxIndex; i++) {

                if (word1[i] == word2[j]) {
                    /*
                        Current character is exact.

                        If mismatch is already used:
                            remaining suffix must be exact.

                        Otherwise:
                            remaining suffix may have one mismatch.
                    */
                    if (mismatchUsed) {
                        if (exact[j + 1] > i) {
                            ans.push_back(i);
                            prev = i;
                            found = true;
                            break;
                        }
                    } else {
                        if (almost[j + 1] > i) {
                            ans.push_back(i);
                            prev = i;
                            found = true;
                            break;
                        }
                    }
                } 
                else {
                    /*
                        Current character is different.

                        This consumes the one allowed mismatch,
                        therefore the rest must match exactly.
                    */
                    if (!mismatchUsed && exact[j + 1] > i) {
                        ans.push_back(i);
                        prev = i;
                        mismatchUsed = true;
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                return {};
            }
        }

        return ans;
    }
};