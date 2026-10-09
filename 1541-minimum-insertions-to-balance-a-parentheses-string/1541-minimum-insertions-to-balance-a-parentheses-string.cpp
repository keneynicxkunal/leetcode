
class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open++;
            } 
            else {
                // If the next character is also ')',
                // consume both as one closing pair.
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } 
                else {
                    // Insert one ')' to complete the pair.
                    insertions++;
                }

                // If no opening '(' exists, insert one.
                if (open > 0) {
                    open--;
                } 
                else {
                    insertions++;
                }
            }
        }

        // Each remaining '(' needs two ')'.
        insertions += open * 2;

        return insertions;
    }
};
