#include <unordered_map>
#include <string>

class Solution {
public:
    int longestPalindrome(std::string s) {
        std::unordered_map<char, int> counts;
        for (char c : s) {
            counts[c]++;
        }
        
        int length = 0;
        bool has_odd = false;
        
        for (auto& [ch, count] : counts) {
            length += (count / 2) * 2;
            if (count % 2 == 1) {
                has_odd = true;
            }
        }
        
        return has_odd ? length + 1 : length;
    }
};