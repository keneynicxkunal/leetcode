class Solution {
public:
    int count = 0;

    void solve(int row, int n,
               vector<bool>& col,
               vector<bool>& diag1,
               vector<bool>& diag2) {

        // All rows completed
        if (row == n) {
            count++;
            return;
        }

        // Try placing queen in every column
        for (int c = 0; c < n; c++) {

            int d1 = row - c + (n - 1);
            int d2 = row + c;

            // If column or diagonal is already occupied
            if (col[c] || diag1[d1] || diag2[d2])
                continue;

            // Place queen
            col[c] = true;
            diag1[d1] = true;
            diag2[d2] = true;

            solve(row + 1, n, col, diag1, diag2);

            // Backtrack
            col[c] = false;
            diag1[d1] = false;
            diag2[d2] = false;
        }
    }

    int totalNQueens(int n) {

        vector<bool> col(n, false);

        // There are 2*n - 1 diagonals
        vector<bool> diag1(2 * n - 1, false);
        vector<bool> diag2(2 * n - 1, false);

        solve(0, n, col, diag1, diag2);

        return count;
    }
};