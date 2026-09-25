class Solution {
public:

    set<string> unite(set<string> a, set<string> b) {
        for (string s : b)
            a.insert(s);

        return a;
    }

    set<string> multiply(set<string> a, set<string> b) {
        set<string> ans;

        for (string x : a) {
            for (string y : b) {
                ans.insert(x + y);
            }
        }

        return ans;
    }

    set<string> parse(string &s, int &i) {

        set<string> result;
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                result = unite(result, current);
                current = {""};
                i++;
            }

            else if (s[i] == '{') {
                i++; // skip {

                set<string> inside = parse(s, i);

                i++; // skip }

                current = multiply(current, inside);
            }

            else {
                string ch = "";
                ch += s[i];

                set<string> letter = {ch};

                current = multiply(current, letter);

                i++;
            }
        }

        result = unite(result, current);

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> ansSet = parse(expression, i);

        vector<string> ans(ansSet.begin(), ansSet.end());

        return ans;
    }
};