class Solution {
public:
    vector<string> ans;

    void solve(int index, string &digits, string &temp, vector<string> &mapping) {
        if (index == digits.size()) {
            ans.push_back(temp);
            return;
        }

        string letters = mapping[digits[index] - '0'];

        for (char ch : letters) {
            temp.push_back(ch);
            solve(index + 1, digits, temp, mapping);
            temp.pop_back(); // Backtrack
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> mapping = {
            "", "", "abc", "def", "ghi", "jkl",
            "mno", "pqrs", "tuv", "wxyz"
        };

        string temp = "";
        solve(0, digits, temp, mapping);

        return ans;
    }
};