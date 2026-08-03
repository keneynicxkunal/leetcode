class Solution {
public:
    unordered_map<string, vector<int>> memo;

    vector<int> diffWaysToCompute(string expression) {
        if (memo.count(expression))
            return memo[expression];

        vector<int> ans;

        for (int i = 0; i < expression.size(); i++) {
            char ch = expression[i];

            if (ch == '+' || ch == '-' || ch == '*') {
                vector<int> left = diffWaysToCompute(expression.substr(0, i));
                vector<int> right = diffWaysToCompute(expression.substr(i + 1));

                for (int a : left) {
                    for (int b : right) {
                        if (ch == '+')
                            ans.push_back(a + b);
                        else if (ch == '-')
                            ans.push_back(a - b);
                        else
                            ans.push_back(a * b);
                    }
                }
            }
        }

        // Base case: expression is a number
        if (ans.empty())
            ans.push_back(stoi(expression));

        return memo[expression] = ans;
    }
};