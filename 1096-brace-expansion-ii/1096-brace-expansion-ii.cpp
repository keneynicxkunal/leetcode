class Solution {
public:

    // Cartesian product / concatenation
    set<string> combine(set<string>& a, set<string>& b) {
        set<string> result;

        for (string x : a) {
            for (string y : b) {
                result.insert(x + y);
            }
        }

        return result;
    }

    set<string> solve(string& s, int& i) {

        // This stores the final answer for this expression
        set<string> result;

        // First part of concatenation
        set<string> current;

        while (i < s.size() && s[i] != '}') {

            set<string> part;

            // Case 1: opening brace
            if (s[i] == '{') {

                i++;  // skip '{'

                part = solve(s, i);

                i++;  // skip '}'
            }

            // Case 2: lowercase letter
            else {
                part.insert(string(1, s[i]));
                i++;
            }

            // Concatenate current with this part
            if (current.empty()) {
                current = part;
            }
            else {
                current = combine(current, part);
            }

            // If comma comes, save current into result
            if (i < s.size() && s[i] == ',') {

                result.insert(current.begin(), current.end());

                current.clear();

                i++;  // skip ','
            }
        }

        // Add the last expression
        result.insert(current.begin(), current.end());

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> ans = solve(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};