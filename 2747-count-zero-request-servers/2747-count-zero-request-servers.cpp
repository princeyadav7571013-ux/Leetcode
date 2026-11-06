
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();

        vector<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());
        sort(logs.begin(), logs.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        unordered_map<int, int> mp;
        vector<int> ans(m);

        int l = 0, r = 0;
        int active = 0;

        for (auto [time, idx] : q) {

            while (r < logs.size() && logs[r][1] <= time) {
                int id = logs[r][0];

                if (mp[id] == 0) active++;
                mp[id]++;
                r++;
            }

            while (l < r && logs[l][1] < time - x) {
                int id = logs[l][0];

                mp[id]--;
                if (mp[id] == 0) active--;

                l++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};
