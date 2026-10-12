
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int cnt[31] = {0};

        // Count set bits at each position
        for (int x : nums) {
            for (int i = 0; i < 31; i++) {
                if ((x >> i) & 1) {
                    cnt[i]++;
                }
            }
        }

        long long ans = 0;

        // Build the largest possible numbers
        for (int j = 0; j < k; j++) {
            long long x = 0;

            for (int i = 0; i < 31; i++) {
                if (cnt[i] > 0) {
                    x |= (1LL << i);
                    cnt[i]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return (int)ans;
    }
};
