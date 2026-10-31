class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][0]: paths arriving while moving right
        // dp[i][j][1]: paths arriving while moving down
        vector<vector<array<int, 2>>> dp(
            m, vector<array<int, 2>>(n, {0, 0})
        );

        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int d = 0; d < 2; d++) {
                    int ways = dp[i][j][d];

                    if (ways == 0) continue;

                    int ni = i;
                    int nj = j;
                    int nd = d;

                    if (grid[i][j] == 1) {
                        // Mirror: right -> down, down -> right
                        nd = 1 - d;

                        if (nd == 0) {
                            nj++;
                        } else {
                            ni++;
                        }
                    } else {
                        // Empty cell: choose right or down
                        if (j + 1 < n) {
                            dp[i][j + 1][0] =
                                (dp[i][j + 1][0] + ways) % MOD;
                        }

                        if (i + 1 < m) {
                            dp[i + 1][j][1] =
                                (dp[i + 1][j][1] + ways) % MOD;
                        }

                        continue;
                    }

                    // Discard paths leaving the grid
                    if (ni < m && nj < n) {
                        dp[ni][nj][nd] =
                            (dp[ni][nj][nd] + ways) % MOD;
                    }
                }
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};