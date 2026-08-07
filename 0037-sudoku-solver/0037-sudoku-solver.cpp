class Solution {
public:
    bool row[9][10] = {};
    bool col[9][10] = {};
    bool box[9][10] = {};

    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {

                    int b = (i / 3) * 3 + (j / 3);

                    for (int num = 1; num <= 9; num++) {
                        if (!row[i][num] && !col[j][num] && !box[b][num]) {

                            board[i][j] = num + '0';
                            row[i][num] = true;
                            col[j][num] = true;
                            box[b][num] = true;

                            if (solve(board))
                                return true;

                            board[i][j] = '.';
                            row[i][num] = false;
                            col[j][num] = false;
                            box[b][num] = false;
                        }
                    }

                    return false;
                }
            }
        }

        return true;
    }

    void solveSudoku(vector<vector<char>>& board) {

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0';
                    row[i][num] = true;
                    col[j][num] = true;
                    int b = (i / 3) * 3 + (j / 3);
                    box[b][num] = true;
                }
            }
        }

        solve(board);
    }
};