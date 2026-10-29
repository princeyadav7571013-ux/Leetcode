class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<int> tin(n), tout(n), depth(n);
        vector<int> parent(n, 0);
        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> pref(n, 0);

        // Iterative DFS: avoids recursion-depth problems.
        vector<int> order;
        order.reserve(n);
        vector<int> st = {0};
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u] && u != 0) continue;
                if (v == 0 && u == 0) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                pref[v] = pref[u] ^ (1 << (s[v] - 'a'));
                st.push_back(v);
            }
        }

        // Build binary-lifting table.
        for (int u = 0; u < n; u++)
            up[0][u] = parent[u];

        for (int j = 1; j < LOG; j++)
            for (int u = 0; u < n; u++)
                up[j][u] = up[j - 1][up[j - 1][u]];

        // Euler tour entry/exit times.
        int timer = 0;
        vector<pair<int, int>> dfs = {{0, 0}};
        vector<int> it(n, 0);

        while (!dfs.empty()) {
            int u = dfs.back().first;

            if (it[u] == 0)
                tin[u] = timer++;

            if (it[u] < (int)adj[u].size()) {
                int v = adj[u][it[u]++];
                if (v == parent[u] && u != 0) continue;
                if (u == 0 && v == 0) continue;
                dfs.push_back({v, 0});
            } else {
                tout[u] = timer - 1;
                dfs.pop_back();
            }
        }

        // Fenwick tree for range XOR updates and point queries.
        vector<int> bit(n + 2, 0);

        auto update = [&](int idx, int val) {
            for (idx++; idx <= n + 1; idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto rangeUpdate = [&](int l, int r, int val) {
            update(l, val);
            if (r + 1 < n) update(r + 1, val);
        };

        auto pointQuery = [&](int idx) {
            int res = 0;
            for (idx++; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        };

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++)
                if (diff & (1 << j))
                    u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return parent[u];
        };

        vector<bool> ans;

        for (string &q : queries) {
            string type;
            int u;
            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));

                if (delta != 0) {
                    rangeUpdate(tin[u], tout[u], delta);
                    s[u] = c;
                }
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int pu = pref[u] ^ pointQuery(tin[u]);
                int pv = pref[v] ^ pointQuery(tin[v]);

                int mask = pu ^ pv ^ (1 << (s[w] - 'a'));

                // At most one odd-frequency character.
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};