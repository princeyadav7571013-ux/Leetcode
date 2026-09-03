class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        // If minimum is odd, we can make all numbers odd
        if (mn % 2 == 1)
            return true;

        // Minimum is even, so all numbers must be even
        for (int x : nums1) {
            if (x % 2 == 1)
                return false;
        }

        return true;
    }
};