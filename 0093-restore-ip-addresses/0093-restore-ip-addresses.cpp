#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> ans;

    void backtrack(string &s, int index, int parts, string current) {

        // We have created 4 parts
        if (parts == 4) {
            // All digits must be used
            if (index == s.length()) {
                current.pop_back(); // remove last '.'
                ans.push_back(current);
            }
            return;
        }

        // Try taking 1, 2, or 3 digits
        for (int len = 1; len <= 3; len++) {

            // Don't go outside the string
            if (index + len > s.length())
                break;

            string part = s.substr(index, len);

            // Leading zero is not allowed
            if (part.length() > 1 && part[0] == '0')
                break;

            // Convert to number
            int num = stoi(part);

            // Must be between 0 and 255
            if (num > 255)
                break;

            // Add this part
            backtrack(
                s,
                index + len,
                parts + 1,
                current + part + "."
            );
        }
    }

    vector<string> restoreIpAddresses(string s) {
        ans.clear();

        // An IP has exactly 4 parts.
        // Therefore length must be between 4 and 12.
        if (s.length() < 4 || s.length() > 12)
            return ans;

        backtrack(s, 0, 0, "");

        return ans;
    }
};