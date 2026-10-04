class Solution {
public:
    string toGoatLatin(string sentence) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        stringstream ss(sentence);
        string word, result = "";
        int index = 1;

        while (ss >> word) {
            // Rule 1 & 2: Check if starting character is a vowel or consonant
            if (vowels.count(word[0])) {
                word += "ma";
            } else {
                word = word.substr(1) + word[0] + "ma";
            }

            // Rule 3: Append 'a' repeated (index) times
            word.append(index, 'a');

            // Construct output string
            if (index > 1) {
                result += " ";
            }
            result += word;

            index++;
        }

        return result;
    }
};