class Solution {
public:
    int minAddToMakeValid(string s) {
        int balance = 0;
        int ans = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            } 
            else {
                balance--;

                // Extra closing parenthesis
                if (balance < 0) {
                    ans++;
                    balance++;
                }
            }
        }

        // Remaining opening parentheses
        ans += balance;

        return ans;
    }
};