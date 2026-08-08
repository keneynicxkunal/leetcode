class Solution {
public:
    bool isNumber(string s) {
        int n = s.size();
        int i = 0;

        // Optional sign
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            i++;
        }

        // Digits before decimal point
        bool hasDigit = false;

        while (i < n && isdigit(s[i])) {
            hasDigit = true;
            i++;
        }

        // Optional decimal point
        if (i < n && s[i] == '.') {
            i++;

            // Digits after decimal point
            while (i < n && isdigit(s[i])) {
                hasDigit = true;
                i++;
            }
        }

        // There must be at least one digit
        if (!hasDigit) {
            return false;
        }

        // Optional exponent
        if (i < n && (s[i] == 'e' || s[i] == 'E')) {
            i++;

            // Exponent must be an integer,
            // so optional sign is allowed.
            if (i < n && (s[i] == '+' || s[i] == '-')) {
                i++;
            }

            bool exponentDigit = false;

            while (i < n && isdigit(s[i])) {
                exponentDigit = true;
                i++;
            }

            // "1e", "1e+", "1e-" are invalid
            if (!exponentDigit) {
                return false;
            }
        }

        // Everything must have been consumed
        return i == n;
    }
};