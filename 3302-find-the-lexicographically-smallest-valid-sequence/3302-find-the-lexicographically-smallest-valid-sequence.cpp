class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        
        int n = word1.size();
        int m = word2.size();

        // last[j] = last possible index in word1
        // where word2[j] can be matched
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // Build last[] from right to left
        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        vector<int> ans(m);

        j = 0;
        bool changed = false;

        // Greedily build lexicographically smallest indices
        for (i = 0; i < n && j < m; i++) {

            // Case 1: Characters already match
            if (word1[i] == word2[j]) {
                ans[j] = i;
                j++;
            }

            // Case 2: Use our one allowed mismatch
            else if (!changed &&
                     (j == m - 1 || i < last[j + 1])) {

                changed = true;
                ans[j] = i;
                j++;
            }
        }

        // If we matched all characters, return answer
        if (j == m)
            return ans;

        // Otherwise impossible
        return {};
    }
};
