class Solution {
public:
    string countAndSay(int n) {
        string result = "1";

        for (int i = 2; i <= n; i++) {
            string next = "";

            int j = 0;

            while (j < result.length()) {
                int count = 0;
                char ch = result[j];

                // Count consecutive same characters
                while (j < result.length() && result[j] == ch) {
                    count++;
                    j++;
                }

                next += to_string(count);
                next += ch;
            }

            result = next;
        }

        return result;
    }
};