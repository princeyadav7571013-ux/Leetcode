
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[j][x] = whether XOR value x is reachable
        // at the current row's column j.
        vector<vector<bool>> dp(n, vector<bool>(1024, false));

        dp[0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    continue;

                vector<bool> curr(1024, false);

                // From the cell above
                if (i > 0) {
                    // The previous row's states were overwritten,
                    // so use the 2D version below for clarity.
                }
            }
        }

        // Full 2D DP: dp[i][j][xor]
        vector<vector<vector<bool>>> reach(
            m, vector<vector<bool>>(
                n, vector<bool>(1024, false)
            )
        );

        reach[0][0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (reach[i - 1][j][x]) {
                            reach[i][j][x ^ grid[i][j]] = true;
                        }
                    }
                }

                if (j > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (reach[i][j - 1][x]) {
                            reach[i][j][x ^ grid[i][j]] = true;
                        }
                    }
                }
            }
        }

        for (int x = 0; x < 1024; x++) {
            if (reach[m - 1][n - 1][x])
                return x;
        }

        return -1;
    }
};
