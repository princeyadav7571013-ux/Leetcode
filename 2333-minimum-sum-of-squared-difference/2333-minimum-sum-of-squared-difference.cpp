
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();

        vector<int> diff(n);
        long long total = 0;
        int maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            maxDiff = max(maxDiff, diff[i]);
        }

        if (total <= k) return 0;

        int left = 0, right = maxDiff;

        while (left < right) {
            int mid = left + (right - left) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid) {
                    needed += d - mid;
                }
            }

            if (needed <= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        int limit = left;
        long long used = 0;
        long long ans = 0;

        for (int d : diff) {
            int reduced = min(d, limit);
            used += d - reduced;
            ans += 1LL * reduced * reduced;
        }

        long long remaining = k - used;

        for (int d : diff) {
            if (remaining == 0) break;

            if (d >= limit && limit > 0) {
                ans -= 1LL * limit * limit;
                ans += 1LL * (limit - 1) * (limit - 1);
                remaining--;
            }
        }

        return ans;
    }
};
