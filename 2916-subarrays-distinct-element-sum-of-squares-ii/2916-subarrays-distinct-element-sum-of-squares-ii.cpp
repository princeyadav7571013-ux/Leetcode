
class Solution {
    static constexpr long long MOD = 1000000007;

    vector<long long> sum, sq, lazy;
    int n;

    void apply(int p, int l, int r, long long v) {
        long long len = r - l + 1;

        sq[p] = (sq[p] + 2 * v * sum[p] % MOD
                 + v * v % MOD * len) % MOD;

        sum[p] = (sum[p] + v * len) % MOD;
        lazy[p] = (lazy[p] + v) % MOD;
    }

    void push(int p, int l, int r) {
        if (lazy[p] == 0 || l == r) return;

        int mid = (l + r) / 2;

        apply(p * 2, l, mid, lazy[p]);
        apply(p * 2 + 1, mid + 1, r, lazy[p]);

        lazy[p] = 0;
    }

    void update(int p, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;

        if (ql <= l && r <= qr) {
            apply(p, l, r, 1);
            return;
        }

        push(p, l, r);
        int mid = (l + r) / 2;

        update(p * 2, l, mid, ql, qr);
        update(p * 2 + 1, mid + 1, r, ql, qr);

        sum[p] = (sum[p * 2] + sum[p * 2 + 1]) % MOD;
        sq[p] = (sq[p * 2] + sq[p * 2 + 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        sum.assign(4 * n + 5, 0);
        sq.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int left = last[nums[i]] + 1;
            update(1, 0, n - 1, left, i);

            ans = (ans + sq[1]) % MOD;
            last[nums[i]] = i;
        }

        return (int)ans;
    }
};
