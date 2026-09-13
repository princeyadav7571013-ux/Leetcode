class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {

        int n = img1.size();

        vector<pair<int, int>> A;
        vector<pair<int, int>> B;

        // Store coordinates of all 1s in img1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (img1[i][j] == 1) {
                    A.push_back({i, j});
                }

                if (img2[i][j] == 1) {
                    B.push_back({i, j});
                }
            }
        }

        map<pair<int, int>, int> mp;

        int ans = 0;

        // Compare every 1 in img1 with every 1 in img2
        for (auto a : A) {
            for (auto b : B) {

                int dx = a.first - b.first;
                int dy = a.second - b.second;

                mp[{dx, dy}]++;

                ans = max(ans, mp[{dx, dy}]);
            }
        }

        return ans;
    }
};