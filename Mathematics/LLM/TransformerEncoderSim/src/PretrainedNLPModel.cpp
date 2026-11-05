#include <vector>
#include <iomanip>
#include <iostream>

class PretrainedNLPModel {
public:

    static std::vector<std::string> tokenize(const std::string &strings) {
        std::vector<std::string> tokens;
        std::string current_word;
        for (char c : strings) {
            if (isalnum(c)) {
                current_word += c;
            } else if (!current_word.empty()) {
                tokens.push_back(current_word);
                current_word = "";
            }
        }
        if (!current_word.empty()) tokens.push_back(current_word);
        return tokens;
    }

};
