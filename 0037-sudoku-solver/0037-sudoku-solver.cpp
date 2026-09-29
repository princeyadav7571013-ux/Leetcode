class Solution {
public:

    bool solve(vector<vector<char>>& board) {

        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {

                // Skip already filled cells
                if (board[row][col] != '.')
                    continue;

                // Try numbers 1 to 9
                for (char num = '1'; num <= '9'; num++) {

                    if (isValid(board, row, col, num)) {

                        // Put number
                        board[row][col] = num;

                        // Recursively solve
                        if (solve(board))
                            return true;

                        // Undo if it doesn't work
                        board[row][col] = '.';
                    }
                }

                // No number works
                return false;
            }
        }

        // Entire board solved
        return true;
    }

    bool isValid(vector<vector<char>>& board,
                 int row,
                 int col,
                 char num) {

        // Check row
        for (int j = 0; j < 9; j++) {
            if (board[row][j] == num)
                return false;
        }

        // Check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num)
                return false;
        }

        // Find 3x3 box
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;

        // Check 3x3 box
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {

                if (board[i][j] == num)
                    return false;
            }
        }

        return true;
    }

    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};