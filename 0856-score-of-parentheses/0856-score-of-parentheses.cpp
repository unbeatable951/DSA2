class Solution {
public:
    int scoreOfParentheses(string s) {
        int score = 0;
        int depth = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                // Check if this closing bracket forms a base "()" core
                if (s[i - 1] == '(') {
                    score += 1 << depth; // 2^depth
                }
            }
        }
        
        return score;
    }
};