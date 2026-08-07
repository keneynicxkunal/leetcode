#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Factors {
        int a = 0, b = 0, c = 0, d = 0;
    };

    // Helper function to extract prime factors (2, 3, 5, 7) from a digit
    Factors get_factors(char ch) {
        int v = ch - '0';
        Factors f;
        if (v == 2) f.a = 1;
        else if (v == 3) f.b = 1;
        else if (v == 4) f.a = 2;
        else if (v == 5) f.c = 1;
        else if (v == 6) { f.a = 1; f.b = 1; }
        else if (v == 7) f.d = 1;
        else if (v == 8) f.a = 3;
        else if (v == 9) f.b = 2;
        return f;
    }

    int dp[60][60];

    // Check if rem_len digits are sufficient to supply all remaining required factors
    bool is_possible(int rem_len, int req_a, int req_b, int req_c, int req_d) {
        if (rem_len < 0) return false;
        req_a = max(0, req_a);
        req_b = max(0, req_b);
        req_c = max(0, req_c);
        req_d = max(0, req_d);
        
        int min_digits_needed = req_c + req_d + dp[min(50, req_a)][min(50, req_b)];
        return rem_len >= min_digits_needed;
    }

public:
    string smallestNumber(string num, long long t) {
        // Step 1: Factorize t into 2^a * 3^b * 5^c * 7^d
        long long temp_t = t;
        int ta = 0, tb = 0, tc = 0, td = 0;
        while (temp_t % 2 == 0) { ta++; temp_t /= 2; }
        while (temp_t % 3 == 0) { tb++; temp_t /= 3; }
        while (temp_t % 5 == 0) { tc++; temp_t /= 5; }
        while (temp_t % 7 == 0) { td++; temp_t /= 7; }
        
        // If t has other prime factors, it's impossible
        if (temp_t > 1) return "-1";

        // Step 2: Precompute DP table for min digits needed for (a, b) factors of (2, 3)
        for (int i = 0; i < 60; i++) {
            for (int j = 0; j < 60; j++) {
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;
        for (int i = 0; i < 60; i++) {
            for (int j = 0; j < 60; j++) {
                if (dp[i][j] == 1e9) continue;
                dp[min(55, i + 3)][j] = min(dp[min(55, i + 3)][j], dp[i][j] + 1); // digit '8'
                dp[i][min(55, j + 2)] = min(dp[i][min(55, j + 2)], dp[i][j] + 1); // digit '9'
                dp[min(55, i + 1)][min(55, j + 1)] = min(dp[min(55, i + 1)][min(55, j + 1)], dp[i][j] + 1); // digit '6'
                dp[min(55, i + 2)][j] = min(dp[min(55, i + 2)][j], dp[i][j] + 1); // digit '4'
                dp[i][min(55, j + 1)] = min(dp[i][min(55, j + 1)], dp[i][j] + 1); // digit '3'
                dp[min(55, i + 1)][j] = min(dp[min(55, i + 1)][j], dp[i][j] + 1); // digit '2'
            }
        }
        
        // Propagate backwards to ensure monotonicity
        for (int i = 55; i >= 0; i--) {
            for (int j = 55; j >= 0; j--) {
                if (i < 55) dp[i][j] = min(dp[i][j], dp[i + 1][j]);
                if (j < 55) dp[i][j] = min(dp[i][j], dp[i][j + 1]);
            }
        }

        int N = num.length();
        int first_zero = N;
        for (int i = 0; i < N; i++) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
        }

        // Prefix factors prefix sums
        vector<int> pref_a(first_zero + 1, 0);
        vector<int> pref_b(first_zero + 1, 0);
        vector<int> pref_c(first_zero + 1, 0);
        vector<int> pref_d(first_zero + 1, 0);

        for (int i = 0; i < first_zero; i++) {
            Factors f = get_factors(num[i]);
            pref_a[i + 1] = pref_a[i] + f.a;
            pref_b[i + 1] = pref_b[i] + f.b;
            pref_c[i + 1] = pref_c[i] + f.c;
            pref_d[i + 1] = pref_d[i] + f.d;
        }

        // Check if num itself is valid
        if (first_zero == N) {
            if (pref_a[N] >= ta && pref_b[N] >= tb && pref_c[N] >= tc && pref_d[N] >= td) {
                return num;
            }
        }

        // Step 3: Try to find a valid string of same length N
        for (int i = min(N - 1, first_zero); i >= 0; i--) {
            int cur_a = ta - pref_a[i];
            int cur_b = tb - pref_b[i];
            int cur_c = tc - pref_c[i];
            int cur_d = td - pref_d[i];

            int start_digit = num[i] - '0' + 1;
            for (int d = start_digit; d <= 9; d++) {
                Factors f = get_factors('0' + d);
                int rem_a = cur_a - f.a;
                int rem_b = cur_b - f.b;
                int rem_c = cur_c - f.c;
                int rem_d = cur_d - f.d;

                int rem_len = N - 1 - i;
                if (is_possible(rem_len, rem_a, rem_b, rem_c, rem_d)) {
                    string ans = num.substr(0, i);
                    ans += (char)('0' + d);

                    // Greedily fill the rest of the suffix
                    int req_a = rem_a, req_b = rem_b, req_c = rem_c, req_d = rem_d;
                    for (int k = i + 1; k < N; k++) {
                        for (int next_d = 1; next_d <= 9; next_d++) {
                            Factors nf = get_factors('0' + next_d);
                            if (is_possible(N - 1 - k, req_a - nf.a, req_b - nf.b, req_c - nf.c, req_d - nf.d)) {
                                ans += (char)('0' + next_d);
                                req_a -= nf.a;
                                req_b -= nf.b;
                                req_c -= nf.c;
                                req_d -= nf.d;
                                break;
                            }
                        }
                    }
                    return ans;
                }
            }
        }

        // Step 4: If no solution of length N exists, construct solution of length > N
        int min_len_t = tc + td + dp[min(50, ta)][min(50, tb)];
        int target_len = max(N + 1, min_len_t);

        string ans = "";
        int req_a = ta, req_b = tb, req_c = tc, req_d = td;
        for (int k = 0; k < target_len; k++) {
            for (int next_d = 1; next_d <= 9; next_d++) {
                Factors nf = get_factors('0' + next_d);
                if (is_possible(target_len - 1 - k, req_a - nf.a, req_b - nf.b, req_c - nf.c, req_d - nf.d)) {
                    ans += (char)('0' + next_d);
                    req_a -= nf.a;
                    req_b -= nf.b;
                    req_c -= nf.c;
                    req_d -= nf.d;
                    break;
                }
            }
        }
        return ans;
    }
};