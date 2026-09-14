class Solution {
public:
    int minCut(string s) {
        int n = s.size();

        // palindrome[i][j] = true if s[i...j] is palindrome
        vector<vector<bool>> palindrome(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {

                if (s[i] == s[j] &&
                    (j - i <= 2 || palindrome[i + 1][j - 1])) {
                    palindrome[i][j] = true;
                }
            }
        }

        // dp[i] = minimum cuts needed for s[0...i]
        vector<int> dp(n);

        for (int i = 0; i < n; i++) {
            if (palindrome[0][i]) {
                dp[i] = 0;
            } else {
                dp[i] = i;

                for (int j = 1; j <= i; j++) {
                    if (palindrome[j][i]) {
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                    }
                }
            }
        }

        return dp[n - 1];
    }
};