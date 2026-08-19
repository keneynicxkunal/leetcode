#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        // row -> bitmask of reserved seats
        unordered_map<int, int> reserved;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            reserved[row] |= (1 << col);
        }

        // Masks for:
        // seats 2,3,4,5
        int left = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);

        // seats 4,5,6,7
        int middle = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);

        // seats 6,7,8,9
        int right = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

        long long ans = 2LL * n;

        for (auto &[row, mask] : reserved) {
            // Initially we assumed this row can fit 2 groups.
            // Now calculate the actual number for this row.

            int groups = 0;

            bool canLeft = (mask & left) == 0;
            bool canMiddle = (mask & middle) == 0;
            bool canRight = (mask & right) == 0;

            if (canLeft && canRight) {
                // [2..5] and [6..9] don't overlap
                groups = 2;
            }
            else if (canLeft || canMiddle || canRight) {
                groups = 1;
            }

            // We had counted 2 for this row initially.
            ans -= 2 - groups;
        }

        return (int)ans;
    }
};