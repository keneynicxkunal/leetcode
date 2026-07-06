class Solution {
public:
    bool canMakeSubsequence(string s, string t) {
        int m = s.size(), n = t.size();

        vector<int> left(m, -1), right(m, -1);


        int j = 0;
        for (int i = 0; i < m; i++) {
            while (j < n && t[j] != s[i]) j++;
            if (j == n) break;
            left[i] = j++;
        }


        if (left[m - 1] != -1) return true;


        j = n - 1;
        for (int i = m - 1; i >= 0; i--) {
            while (j >= 0 && t[j] != s[i]) j--;
            if (j < 0) break;
            right[i] = j--;
        }

        for (int i = 0; i < m; i++) {
            int L = -1, R = n;

            if (i > 0) {
                if (left[i - 1] == -1) continue;
                L = left[i - 1];
            }

            if (i < m - 1) {
                if (right[i + 1] == -1) continue;
                R = right[i + 1];
            }

            if (L + 1 < R) return true;
        }

        return false;
    }
};