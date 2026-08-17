#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {

        // Overflow case:
        // INT_MIN / -1 = 2147483648
        // which is greater than INT_MAX
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Determine the sign of the answer
        bool negative = (dividend < 0) ^ (divisor < 0);

        // Convert to positive long long values
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);

        long long quotient = 0;

        while (a >= b) {

            // Find the largest multiple of divisor
            // that can be subtracted from dividend
            long long current = b;
            long long multiple = 1;

            while ((current << 1) <= a) {
                current <<= 1;
                multiple <<= 1;
            }

            a -= current;
            quotient += multiple;
        }

        // Apply sign
        if (negative) {
            quotient = -quotient;
        }

        // Clamp to 32-bit integer range
        if (quotient > INT_MAX) {
            return INT_MAX;
        }

        if (quotient < INT_MIN) {
            return INT_MIN;
        }

        return (int)quotient;
    }
};