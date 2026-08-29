class Solution {
public:

    vector<string> ans;

    string phone[10] = {
        "", "", "abc", "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void backtrack(string digits, int index, string current) {

        // We have selected one letter for every digit
        if (index == digits.length()) {
            ans.push_back(current);
            return;
        }

        // Current digit
        int digit = digits[index] - '0';

        // Try every letter of this digit
        for (char ch : phone[digit]) {

            current.push_back(ch);

            // Move to next digit
            backtrack(digits, index + 1, current);

            // Remove the last letter
            current.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {

        if (digits.empty())
            return {};

        backtrack(digits, 0, "");

        return ans;
    }
};