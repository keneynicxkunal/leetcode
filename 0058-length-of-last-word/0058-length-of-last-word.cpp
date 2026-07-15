class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.length();
        int len = 0;

        // Skip trailing spaces
        int i = n - 1;
        while (i >= 0 && s[i] == ' ') {
            i--;
        }

        // Count characters of the last word
        while (i >= 0 && s[i] != ' ') {
            len++;
            i--;
        }

        return len;
    }
};