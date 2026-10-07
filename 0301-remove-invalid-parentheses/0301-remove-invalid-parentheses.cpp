class Solution {
public:
    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(')
                balance++;

            else if (c == ')') {
                balance--;

                if (balance < 0)
                    return false;
            }
        }

        return balance == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;

        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            if (isValid(cur)) {
                ans.push_back(cur);
                found = true;
            }

            // Once we found valid strings at this level,
            // don't generate strings with more removals.
            if (found)
                continue;

            for (int i = 0; i < cur.size(); i++) {

                // Only remove parentheses
                if (cur[i] != '(' && cur[i] != ')')
                    continue;

                // Avoid removing identical consecutive parentheses
                if (i > 0 && cur[i] == cur[i - 1])
                    continue;

                string next = cur.substr(0, i) + cur.substr(i + 1);

                if (!visited.count(next)) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};