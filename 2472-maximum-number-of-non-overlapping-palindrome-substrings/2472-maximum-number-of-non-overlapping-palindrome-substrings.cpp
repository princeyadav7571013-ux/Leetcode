class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // pal[i][j] = true if s[i..j] is palindrome
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] &&
                    (j - i <= 1 || pal[i + 1][j - 1])) {
                    pal[i][j] = true;
                }
            }
        }

        // dp[i] = maximum number of valid palindromes
        // using s[0..i-1]
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Don't take a palindrome ending at i-1
            dp[i] = dp[i - 1];

            // Try every palindrome ending at i-1
            for (int start = 0; start <= i - k; start++) {
                if (pal[start][i - 1]) {
                    dp[i] = max(dp[i], dp[start] + 1);
                }
            }
        }

        return dp[n];
    }
};