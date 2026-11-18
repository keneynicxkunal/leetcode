#include <string>

using namespace std;

class Solution {
public:
    int minChanges(string s) {
        int changes = 0;
        
        // Iterate through the string in steps of 2 to check each adjacent pair
        for (int i = 0; i < s.length(); i += 2) {
            if (s[i] != s[i + 1]) {
                changes++;
            }
        }
        
        return changes;
    }
};