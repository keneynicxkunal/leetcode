#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;

    ll gcd(ll a, ll b) {
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    ll lcm(ll a, ll b) {
        return a / gcd(a, b) * b;
    }

    // Count distinct positive integers <= x
    // that are divisible by at least one coin.
    ll countValid(ll x, vector<int>& coins) {
        int n = coins.size();
        ll ans = 0;

        // Inclusion-Exclusion
        for (int mask = 1; mask < (1 << n); mask++) {
            ll multiple = 1;
            int bits = 0;
            bool overflow = false;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    multiple = lcm(multiple, (ll)coins[i]);

                    if (multiple > x) {
                        overflow = true;
                        break;
                    }
                }
            }

            if (overflow || multiple > x)
                continue;

            ll cnt = x / multiple;

            if (bits % 2 == 1)
                ans += cnt;
            else
                ans -= cnt;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        ll lo = 1;
        ll hi = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;

            if (countValid(mid, coins) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};