class Solution {
public:
    vector<string> result;

    void backtrack(string current, int open, int close, int n) {

        // If length becomes 2*n, we have a valid answer
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }

        // We can add '(' if open brackets are still available
        if (open < n) {
            backtrack(current + '(', open + 1, close, n);
        }

        // We can add ')' only when it won't become invalid
        if (close < open) {
            backtrack(current + ')', open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        backtrack("", 0, 0, n);
        return result;
    }
};