class Solution {
public:
    int n, m;

    void dfs(vector<vector<char>>& board, int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= m ||
            board[r][c] != 'O') {
            return;
        }

        board[r][c] = 'S';

        dfs(board, r + 1, c);
        dfs(board, r - 1, c);
        dfs(board, r, c + 1);
        dfs(board, r, c - 1);
    }

    void solve(vector<vector<char>>& board) {
        n = board.size();
        m = board[0].size();

        // First and last columns
        for (int i = 0; i < n; i++) {
            dfs(board, i, 0);
            dfs(board, i, m - 1);
        }

        // First and last rows
        for (int j = 0; j < m; j++) {
            dfs(board, 0, j);
            dfs(board, n - 1, j);
        }

        // Convert remaining O -> X
        // Convert safe S -> O
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == 'S')
                    board[i][j] = 'O';
            }
        }
    }
};