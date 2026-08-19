#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.length() < t.length())
            return "";

        // Required frequency of each character
        vector<int> need(128, 0);

        for (char c : t) {
            need[c]++;
        }

        int left = 0;
        int right = 0;

        int required = t.length();
        int minLength = INT_MAX;
        int start = 0;

        while (right < s.length()) {
            char c = s[right];

            // If this character is still needed
            if (need[c] > 0) {
                required--;
            }

            need[c]--;
            right++;

            // Window is valid
            while (required == 0) {

                // Update minimum window
                if (right - left < minLength) {
                    minLength = right - left;
                    start = left;
                }

                char leftChar = s[left];
                need[leftChar]++;

                // Removing a required character makes window invalid
                if (need[leftChar] > 0) {
                    required++;
                }

                left++;
            }
        }

        if (minLength == INT_MAX)
            return "";

        return s.substr(start, minLength);
    }
};