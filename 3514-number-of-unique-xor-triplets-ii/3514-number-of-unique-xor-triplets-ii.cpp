class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return 1;

        unordered_set<int> pairXor;
        unordered_set<int> ans;

        // XOR of all distinct pairs
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                pairXor.insert(nums[i] ^ nums[j]);
            }
        }

        // Pair XOR with every element
        for (int x : pairXor) {
            for (int num : nums) {
                ans.insert(x ^ num);
            }
        }

        // Triplets with all three indices equal (a ^ a ^ a = a)
        for (int num : nums) {
            ans.insert(num);
        }

        return ans.size();
    }
};