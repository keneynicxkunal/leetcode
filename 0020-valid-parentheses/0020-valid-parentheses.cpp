class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char c : s) {

            // Opening brackets
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            }

            // Closing brackets
            else {
                // No opening bracket available
                if (st.empty()) {
                    return false;
                }

                char top = st.top();

                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    return false;
                }

                st.pop();
            }
        }

        // All brackets must be closed
        return st.empty();
    }
};