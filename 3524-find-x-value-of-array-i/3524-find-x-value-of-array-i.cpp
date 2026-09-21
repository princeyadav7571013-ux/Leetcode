class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // dp[r] = number of subarrays ending at the
        // previous position whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            int val = num % k;

            vector<long long> newDp(k, 0);

            // Start a new subarray with only nums[i]
            newDp[val]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                int newR = (r * val) % k;
                newDp[newR] += dp[r];
            }

            // Add current subarrays to final answer
            for (int r = 0; r < k; r++) {
                ans[r] += newDp[r];
            }

            dp = newDp;
        }

        return ans;
    }
};