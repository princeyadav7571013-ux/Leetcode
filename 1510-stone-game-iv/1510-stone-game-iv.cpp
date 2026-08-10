class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        // dp[i] = true means Alice can win with i stones
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                // If after removing j*j stones,
                // opponent is in a losing position
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};