#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char c : s) {

            if (c == '(') {
                low++;
                high++;
            }

            else if (c == ')') {
                low--;
                high--;
            }

            else { // '*'
                low--;   // '*' as ')'
                high++;  // '*' as '('
            }

            // Too many ')' 
            if (high < 0) {
                return false;
            }

            // Minimum can't be negative
            if (low < 0) {
                low = 0;
            }
        }

        // Some possible interpretation must have 0 unmatched '('
        return low == 0;
    }
};