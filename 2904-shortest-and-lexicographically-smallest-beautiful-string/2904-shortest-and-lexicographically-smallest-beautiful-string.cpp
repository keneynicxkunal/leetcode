class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        vector<int> pos;

        // Store positions of all 1s
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                pos.push_back(i);
            }
        }

        // Not enough 1s
        if (pos.size() < k)
            return "";

        int minLen = INT_MAX;
        string ans = "";

        // Consider every group of k consecutive 1s
        for (int i = 0; i + k - 1 < pos.size(); i++) {
            int leftOne = pos[i];
            int rightOne = pos[i + k - 1];

            int len = rightOne - leftOne + 1;

            string cur = s.substr(leftOne, len);

            if (len < minLen) {
                minLen = len;
                ans = cur;
            }
            else if (len == minLen) {
                ans = min(ans, cur);
            }
        }

        return ans;
    }
};