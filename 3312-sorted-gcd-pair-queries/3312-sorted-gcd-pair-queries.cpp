

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = 0;
        for (int num : nums) {
            if (num > max_val) {
                max_val = num;
            }
        }
        
        // Count frequencies of each number in nums
        vector<long long> count(max_val + 1, 0);
        for (int num : nums) {
            count[num]++;
        }
        
        // Array to store the EXACT number of pairs that have a specific GCD
        vector<long long> exact_gcd(max_val + 1, 0);
        
        // Process from max_val down to 1
        for (int i = max_val; i >= 1; --i) {
            long long multiples_count = 0;
            
            // Count how many numbers in the array are multiples of i
            for (int j = i; j <= max_val; j += i) {
                multiples_count += count[j];
            }
            
            // Total pairs where both numbers are multiples of i
            long long pairs = multiples_count * (multiples_count - 1) / 2;
            
            // Subtract pairs where the GCD is a strict multiple of i
            for (int j = 2 * i; j <= max_val; j += i) {
                pairs -= exact_gcd[j];
            }
            
            exact_gcd[i] = pairs;
        }
        
        // Prefix sums to help answer index queries
        vector<long long> prefix(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            prefix[i] = prefix[i - 1] + exact_gcd[i];
        }
        
        // Answer each query using binary search
        vector<int> answer;
        answer.reserve(queries.size());
        
        for (long long q : queries) {
            // Find the first index where the prefix sum is greater than the query index
            auto it = upper_bound(prefix.begin(), prefix.end(), q);
            answer.push_back(distance(prefix.begin(), it));
        }
        
        return answer;
    }
};