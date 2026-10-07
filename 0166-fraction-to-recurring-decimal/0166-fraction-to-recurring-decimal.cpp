class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {

        // If numerator is 0
        if (numerator == 0)
            return "0";

        string ans;

        // Check negative result
        if ((numerator < 0) ^ (denominator < 0))
            ans += "-";

        // Convert to long long to avoid overflow
        long long num = llabs((long long)numerator);
        long long den = llabs((long long)denominator);

        // Integer part
        ans += to_string(num / den);

        long long remainder = num % den;

        // No decimal part
        if (remainder == 0)
            return ans;

        ans += ".";

        // remainder -> position in answer
        unordered_map<long long, int> mp;

        while (remainder != 0) {

            // Repeating remainder found
            if (mp.find(remainder) != mp.end()) {
                int pos = mp[remainder];
                ans.insert(pos, "(");
                ans += ")";
                break;
            }

            // Store position before processing remainder
            mp[remainder] = ans.size();

            remainder *= 10;

            ans += to_string(remainder / den);

            remainder %= den;
        }

        return ans;
    }
};