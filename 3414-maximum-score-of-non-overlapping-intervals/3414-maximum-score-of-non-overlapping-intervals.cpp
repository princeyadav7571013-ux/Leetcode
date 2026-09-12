class Solution {
public:
    using T = pair<long long, vector<int>>;

    vector<vector<int>> a;

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<int, 4>> v;

        for (int i = 0; i < n; i++) {
            v.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by left
        sort(v.begin(), v.end());

        vector<vector<T>> dp(n + 1, vector<T>(5));

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {

                // Option 1: Skip current interval
                T skip = dp[i + 1][k];

                // Option 2: Take current interval
                int right = v[i][1];
                int weight = v[i][2];
                int index = v[i][3];

                // Find first interval whose left > right
                int lo = i + 1;
                int hi = n;

                while (lo < hi) {
                    int mid = lo + (hi - lo) / 2;

                    if (v[mid][0] <= right)
                        lo = mid + 1;
                    else
                        hi = mid;
                }

                int next = lo;

                T take = dp[next][k - 1];
                take.first += weight;
                take.second.push_back(index);

                // Keep indices sorted
                sort(take.second.begin(), take.second.end());

                // Choose better answer
                if (take.first > skip.first ||
                    (take.first == skip.first &&
                     take.second < skip.second)) {

                    dp[i][k] = take;

                } else {
                    dp[i][k] = skip;
                }
            }
        }

        return dp[0][4].second;
    }
};