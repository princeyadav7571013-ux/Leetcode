class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Path contains m+n-1 cells.
        // For balance to become 0, path length must be even.
        if ((m + n - 1) % 2 != 0)
            return false;

        // dp[j][balance]
        vector<vector<bool>> dp(n, vector<bool>(m + n + 1, false));

        // Starting cell must be '('
        if (grid[0][0] == '(')
            dp[0][1] = true;
        else
            return false;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                // IMPORTANT:
                // Create a fresh state for this cell.
                vector<bool> current(m + n + 1, false);

                int change = (grid[i][j] == '(') ? 1 : -1;

                for (int balance = 0; balance <= m + n; balance++) {

                    bool reachable = false;

                    // Come from top
                    if (i > 0 && dp[j][balance])
                        reachable = true;

                    // Come from left
                    if (j > 0 && dp[j - 1][balance])
                        reachable = true;

                    if (!reachable)
                        continue;

                    int newBalance = balance + change;

                    // Balance can never be negative
                    if (newBalance >= 0 &&
                        newBalance <= m + n) {

                        current[newBalance] = true;
                    }
                }

                // Store ONLY the states of this cell
                dp[j] = current;
            }
        }

        return dp[n - 1][0];
    }
};