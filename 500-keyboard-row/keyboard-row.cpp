class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        int rowMap[26];
        std::string r1 = "qwertyuiop", r2 = "asdfghjkl", r3 = "zxcvbnm";

        for (char c : r1) rowMap[c - 'a'] = 1;
        for (char c : r2) rowMap[c - 'a'] = 2;
        for (char c : r3) rowMap[c - 'a'] = 3;

        std::vector<std::string> result;

        for (const std::string& word : words) {
            int targetRow = rowMap[std::tolower(word[0]) - 'a'];
            bool isValid = true;

            for (size_t i = 1; i < word.length(); ++i) {
                if (rowMap[std::tolower(word[i]) - 'a'] != targetRow) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                result.push_back(word);
            }
        }

        return result;
        
        
    }
};