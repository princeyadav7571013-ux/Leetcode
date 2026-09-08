class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        int n = words.size();
        int i = 0;

        while (i < n) {
            int j = i;
            int letters = 0;

            // Find words that can fit in this line
            while (j < n &&
                   letters + words[j].size() + (j - i) <= maxWidth) {
                letters += words[j].size();
                j++;
            }

            int wordCount = j - i;
            int spaces = maxWidth - letters;

            string line;

            // Last line OR line contains only one word
            if (j == n || wordCount == 1) {
                for (int k = i; k < j; k++) {
                    line += words[k];

                    if (k != j - 1)
                        line += " ";
                }

                // Remaining spaces at the end
                line += string(maxWidth - line.size(), ' ');
            }
            else {
                // Number of gaps
                int gaps = wordCount - 1;

                int spaceEach = spaces / gaps;
                int extra = spaces % gaps;

                for (int k = i; k < j; k++) {
                    line += words[k];

                    if (k != j - 1) {
                        line += string(spaceEach, ' ');

                        // Extra spaces go to leftmost gaps
                        if (extra > 0) {
                            line += " ";
                            extra--;
                        }
                    }
                }
            }

            ans.push_back(line);
            i = j;
        }

        return ans;
    }
};