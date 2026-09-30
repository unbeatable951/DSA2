class Solution {
public:
    bool detectCapitalUse(string word) {
        int capCount = 0;
        int n = word.length();
        
        for (char c : word) {
            if (isupper(c)) {
                capCount++;
            }
        }
        
        return capCount == n || capCount == 0 || (capCount == 1 && isupper(word[0]));
        
    }
};