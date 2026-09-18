class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        // First and last occurrence of every character
        vector<int> first(26, n), last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        // Find the smallest valid interval starting from position l
        // A valid interval [l, r] must contain ALL occurrences
        // of every character appearing inside it.
        vector<pair<int, int>> intervals;

        for (int c = 0; c < 26; c++) {
            if (last[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];
            bool valid = true;

            for (int i = l; i <= r; i++) {
                int x = s[i] - 'a';

                // This character occurs before l,
                // so [l,r] cannot contain all of its occurrences.
                if (first[x] < l) {
                    valid = false;
                    break;
                }

                r = max(r, last[x]);
            }

            if (valid) {
                intervals.push_back({r, l});
            }
        }

        // Sort by ending position.
        sort(intervals.begin(), intervals.end());

        vector<string> ans;
        int prevEnd = -1;

        // Greedily choose the interval with earliest ending position.
        for (auto [r, l] : intervals) {
            if (l > prevEnd) {
                ans.push_back(s.substr(l, r - l + 1));
                prevEnd = r;
            }
        }

        return ans;
    }
};