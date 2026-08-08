class Solution {
public:
    void reverseString(vector<char>& s) {
        int str = 0 , end = s.size()-1;


        while(str<end) {
            swap(s[str++] ,s[end--]);
        }
    }
};