class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> left, right;
        long long leftSum = 0, rightSum = 0;

        auto balance = [&]() {
            while (left.size() > right.size() + 1) {
                int val = *left.rbegin();
                left.erase(left.find(val));
                leftSum -= val;

                right.insert(val);
                rightSum += val;
            }

            while (left.size() < right.size()) {
                int val = *right.begin();
                right.erase(right.find(val));
                rightSum -= val;

                left.insert(val);
                leftSum += val;
            }
        };

        auto add = [&](int val) {
            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                leftSum += val;
            } else {
                right.insert(val);
                rightSum += val;
            }
            balance();
        };

        auto remove = [&](int val) {
            auto it = left.find(val);

            if (it != left.end()) {
                left.erase(it);
                leftSum -= val;
            } else {
                it = right.find(val);
                right.erase(it);
                rightSum -= val;
            }

            balance();
        };

        auto getCost = [&]() -> long long {
            long long median = *left.rbegin();

            return median * (long long)left.size() - leftSum
                 + rightSum - median * (long long)right.size();
        };

        // Calculate the cost of every window of length x.
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);

            cost[i - x + 1] = getCost();
        }

        // dp[t][i] = minimum cost using exactly t windows
        // among the first i elements.
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int t = 1; t <= k; t++) {
            for (int i = 1; i <= n; i++) {
                // Skip the current element.
                dp[t][i] = dp[t][i - 1];

                // Select a window ending at position i - 1.
                if (i >= x && dp[t - 1][i - x] != INF) {
                    dp[t][i] = min(
                        dp[t][i],
                        dp[t - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};