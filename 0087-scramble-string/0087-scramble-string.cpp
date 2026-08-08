class Solution {
public:
    string a, b;

    // memo[l1][l2][len]
    // -1 = not calculated
    //  0 = false
    //  1 = true
    int memo[30][30][31];

    bool solve(int l1, int l2, int len) {
        int &res = memo[l1][l2][len];

        if (res != -1)
            return res;

        // Same substring
        if (a.compare(l1, len, b, l2, len) == 0) {
            return res = 1;
        }

        // Check character frequencies.
        // If they differ, scrambling is impossible.
        int freq[26] = {};

        for (int i = 0; i < len; i++) {
            freq[a[l1 + i] - 'a']++;
            freq[b[l2 + i] - 'a']--;
        }

        for (int i = 0; i < 26; i++) {
            if (freq[i] != 0)
                return res = 0;
        }

        // Try every possible split.
        for (int k = 1; k < len; k++) {

            /*
                Case 1: No swap

                a: [ left | right ]
                b: [ left | right ]

                a[l1 ... l1+k-1]  <-> b[l2 ... l2+k-1]
                a[l1+k ...]       <-> b[l2+k ...]
            */
            if (solve(l1, l2, k) &&
                solve(l1 + k, l2 + k, len - k)) {
                return res = 1;
            }

            /*
                Case 2: Swap

                a: [ left | right ]
                b: [ right | left ]

                a left  <-> b right
                a right <-> b left
            */
            if (solve(l1, l2 + len - k, k) &&
                solve(l1 + k, l2, len - k)) {
                return res = 1;
            }
        }

        return res = 0;
    }

    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size())
            return false;

        a = s1;
        b = s2;

        memset(memo, -1, sizeof(memo));

        return solve(0, 0, s1.size());
    }
};