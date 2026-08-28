class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int m = n / 2;

        // Count characters in s
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Check whether a palindrome is possible
        int odd = 0;
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                middle = char('a' + i);
            }
        }

        if (odd > 1) {
            return "";
        }

        // Count of characters available in the first half
        vector<int> halfCnt(26);

        for (int i = 0; i < 26; i++) {
            halfCnt[i] = freq[i] / 2;
        }

        // Build complete palindrome from its first half
        auto build = [&](const string& half) {
            string ans = half;

            if (n % 2) {
                ans += middle;
            }

            string rev = half;
            reverse(rev.begin(), rev.end());

            ans += rev;

            return ans;
        };

        string prefix = target.substr(0, m);

        /*
            STEP 1:
            Try to make the first half exactly equal to target's
            first half.
        */

        vector<int> rem = halfCnt;
        bool possible = true;

        for (char c : prefix) {
            int x = c - 'a';

            if (rem[x] == 0) {
                possible = false;
                break;
            }

            rem[x]--;
        }

        if (possible) {
            string candidate = build(prefix);

            // The half is equal, so we must compare the complete
            // palindrome with target.
            if (candidate > target) {
                return candidate;
            }
        }

        /*
            STEP 2:
            Find the smallest half which is lexicographically
            GREATER than target's first half.

            We try to change the rightmost possible position.

            Example:

                target half = "ab"

                Change position 1:
                    b > b ? no

                Change position 0:
                    b > a -> "ba"

                Fill remaining characters minimally.

                    "ba" -> "baab"
        */

        for (int i = m - 1; i >= 0; i--) {

            // Characters used by prefix [0 ... i-1]
            vector<int> remaining = halfCnt;

            bool validPrefix = true;

            for (int j = 0; j < i; j++) {
                int x = prefix[j] - 'a';

                if (remaining[x] == 0) {
                    validPrefix = false;
                    break;
                }

                remaining[x]--;
            }

            if (!validPrefix) {
                continue;
            }

            int current = prefix[i] - 'a';

            // Find the smallest character greater than target[i]
            for (int c = current + 1; c < 26; c++) {

                if (remaining[c] == 0) {
                    continue;
                }

                string half = prefix.substr(0, i);

                // Make this position just slightly larger
                half += char('a' + c);

                remaining[c]--;

                // Fill the rest with smallest possible characters
                for (int x = 0; x < 26; x++) {
                    half += string(remaining[x], char('a' + x));
                }

                string candidate = build(half);

                if (candidate > target) {
                    return candidate;
                }

                remaining[c]++;
            }
        }

        return "";
    }
};