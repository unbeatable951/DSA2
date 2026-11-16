
class Solution {
public:
    string digitSum(string s, int k) {

        while (s.size() > k) {

            string ans = "";

            for (int i = 0; i < s.size(); i += k) {

                int sum = 0;

                // Calculate sum of digits in current group
                for (int j = i; j < min(i + k, (int)s.size()); j++) {
                    sum += s[j] - '0';
                }

                // Convert integer sum into string
                ans += to_string(sum);
            }

            s = ans;
        }

        return s;
    }
};
