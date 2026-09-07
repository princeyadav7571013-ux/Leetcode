class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        long long dp = 0;

        // last[c] = dp value before the previous occurrence of c
        vector<long long> last(26, 0);

        for (char c : s) {
            int x = c - 'a';

            long long newDp = (2 * dp + 1 - last[x] + MOD) % MOD;

            last[x] = dp + 1;
            dp = newDp;
        }

        return dp;
    }
};