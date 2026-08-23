class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int diff = 0;
        int leftQ = 0;
        int rightQ = 0;

        // Left half
        for (int i = 0; i < half; i++) {
            if (num[i] == '?') {
                leftQ++;
            } else {
                diff += num[i] - '0';
            }
        }

        // Right half
        for (int i = half; i < n; i++) {
            if (num[i] == '?') {
                rightQ++;
            } else {
                diff -= num[i] - '0';
            }
        }

        int qDiff = rightQ - leftQ;

        // Odd difference in number of '?' => Alice wins
        if (qDiff % 2 != 0)
            return true;

        // Bob can force equality only in this exact signed case
        return diff != 9 * qDiff / 2;
    }
};