class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        string ans(n, ' ');

        // Match target as much as possible
        for (int i = 0; i < n; i++) {
            int x = target[i] - 'a';

            if (cnt[x] > 0) {
                ans[i] = target[i];
                cnt[x]--;
            } 
            else {
                // We cannot match target[i].
                // Try to put a larger character here.
                for (int c = x + 1; c < 26; c++) {
                    if (cnt[c] > 0) {
                        ans[i] = char('a' + c);
                        cnt[c]--;

                        // Fill remaining positions minimally
                        int pos = i + 1;

                        for (int ch = 0; ch < 26; ch++) {
                            while (cnt[ch] > 0) {
                                ans[pos++] = char('a' + ch);
                                cnt[ch]--;
                            }
                        }

                        return ans;
                    }
                }

                // No larger character here.
                // Backtrack.
                for (int j = i - 1; j >= 0; j--) {
                    cnt[ans[j] - 'a']++;

                    int targetChar = target[j] - 'a';

                    for (int c = targetChar + 1; c < 26; c++) {
                        if (cnt[c] > 0) {
                            ans[j] = char('a' + c);
                            cnt[c]--;

                            // Fill rest with smallest characters
                            int pos = j + 1;

                            for (int ch = 0; ch < 26; ch++) {
                                while (cnt[ch] > 0) {
                                    ans[pos++] = char('a' + ch);
                                    cnt[ch]--;
                                }
                            }

                            return ans;
                        }
                    }

                    ans[j] = ' ';
                }

                return "";
            }
        }

        // We matched target exactly.
        // Need a strictly greater permutation.
        for (int j = n - 1; j >= 0; j--) {
            cnt[ans[j] - 'a']++;

            int targetChar = target[j] - 'a';

            for (int c = targetChar + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    ans[j] = char('a' + c);
                    cnt[c]--;

                    // Fill remaining positions minimally
                    int pos = j + 1;

                    for (int ch = 0; ch < 26; ch++) {
                        while (cnt[ch] > 0) {
                            ans[pos++] = char('a' + ch);
                            cnt[ch]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};