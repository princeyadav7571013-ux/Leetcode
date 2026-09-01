class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        // Give every litter a number: 0, 1, 2, ...
        vector<vector<int>> id(m, vector<int>(n, -1));

        int sr = 0, sc = 0;
        int litterCount = 0;

        // Find S and assign IDs to L
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                else if (classroom[i][j] == 'L') {
                    id[i][j] = litterCount;
                    litterCount++;
                }
            }
        }

        // No litter
        if (litterCount == 0)
            return 0;

        int totalMasks = 1 << litterCount;

        /*
            State:

            row
            col
            remaining energy
            mask
        */

        queue<tuple<int, int, int, int>> q;

        // Initially no litter is collected.
        // Therefore all bits are 1.
        int startMask = totalMasks - 1;

        q.push({sr, sc, energy, startMask});

        /*
            visited[row][col][energy][mask]
        */
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(totalMasks, false)
                )
            )
        );

        visited[sr][sc][energy][startMask] = true;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            int sz = q.size();

            // All states at the same distance
            while (sz--) {

                auto [r, c, curEnergy, mask] = q.front();
                q.pop();

                // All litter collected
                if (mask == 0)
                    return moves;

                // Cannot move anymore
                if (curEnergy == 0)
                    continue;

                // Try 4 directions
                for (int k = 0; k < 4; k++) {

                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    // Outside grid
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    // -------------------------
                    // Calculate new energy
                    // -------------------------

                    int newEnergy;

                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }
                    else {
                        newEnergy = curEnergy - 1;
                    }

                    // -------------------------
                    // Update litter mask
                    // -------------------------

                    int newMask = mask;

                    if (classroom[nr][nc] == 'L') {

                        int litterID = id[nr][nc];

                        // Mark this litter as collected
                        newMask &= ~(1 << litterID);
                    }

                    // -------------------------
                    // Visit new state
                    // -------------------------

                    if (!visited[nr][nc][newEnergy][newMask]) {

                        visited[nr][nc][newEnergy][newMask] = true;

                        q.push({
                            nr,
                            nc,
                            newEnergy,
                            newMask
                        });
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};