
class Solution {
public:
    int hammingWeight(int n) {
        unsigned int num = (unsigned int)n;
        int count = 0;

        while (num != 0) {
            count += (num & 1U);
            num >>= 1;
        }

        return count;
    }
};
