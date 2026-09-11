class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        
        // Count frequency of each digit
        vector<int> freq(10, 0);

        for (int digit : digits) {
            freq[digit]++;
        }

        int ans = 0;

        // First digit: 1 to 9
        for (int first = 1; first <= 9; first++) {

            if (freq[first] == 0)
                continue;

            // Second digit: 0 to 9
            for (int second = 0; second <= 9; second++) {

                if (freq[second] == 0)
                    continue;

                // Third digit must be even
                for (int third = 0; third <= 8; third += 2) {

                    if (freq[third] == 0)
                        continue;

                    // Use one copy of each digit
                    freq[first]--;
                    freq[second]--;
                    freq[third]--;

                    // Check whether we have enough copies
                    if (freq[first] >= 0 &&
                        freq[second] >= 0 &&
                        freq[third] >= 0) {
                        ans++;
                    }

                    // Restore frequencies
                    freq[first]++;
                    freq[second]++;
                    freq[third]++;
                }
            }
        }

        return ans;
    }
};