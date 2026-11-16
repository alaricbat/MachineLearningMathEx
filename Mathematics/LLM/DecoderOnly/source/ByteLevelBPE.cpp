#include "../include/ByteLevelBPE.h"

#include <sstream>
#include <iomanip>

std::vector<std::string> ByteLevelBPE::split(const std::string &dataset) {

    std::vector<std::string> arr;
    std::string current;

    auto flush = [&]() {
        if (!current.empty()) {
            arr.push_back(std::move(current));
        }
        current.clear();
    };

    size_t i = 0;
    while (i < dataset.size()) {

        unsigned char c = dataset[i];

        if (c == '[' || c == '<') {
            char close_char = (c == '[') ? ']' : '>';
            size_t close_point = dataset.find(close_char, i + 1);
            size_t newline_point = dataset.find('\n', i + 1);

            if (close_point != std::string::npos &&
                (newline_point == std::string::npos || close_point < newline_point) &&
                (close_point - i) <= 64) {
                flush();
                arr.push_back(dataset.substr(i, close_point - i + 1));
                i = close_point + 1;
                continue;
            }
        }

        size_t char_len = 1;
        if ((c & 0x80) == 0x00) {
            char_len = 1;
        } else if ((c & 0xE0) == 0xC0) {
            char_len = 2;
        } else if ((c & 0xF0) == 0xE0) {
            char_len = 3;
        } else if ((c & 0xF8) == 0xF0) {
            char_len = 4;
        }

        if (i + char_len > dataset.size()) {
            char_len = dataset.size() - i;
        }

        std::string token = dataset.substr(i, char_len);

        if (char_len == 1) {
            if (std::isspace(c)) {
                flush();
            } else if (std::isdigit(c) || std::ispunct(c)) {
                flush();
                arr.push_back(token);
            } else {
                current += token;
            }
        } else {
            uint32_t cp = getUnicodeCodePoint(dataset, i, char_len);
            if (!isHanzi(cp)) {
                flush();
                arr.push_back(token);
            } else {
                current += token;
            }
        }

        i += char_len;
    }

    flush();
    return arr;

}

std::unordered_map<std::string, int> ByteLevelBPE::computeWordFreqs(const std::vector<std::string> &words) {

    std::unordered_map<std::string, int> freqs;

    for (const auto &tmp : words) {
        auto it = freqs.find(tmp);
        if (it != freqs.end()) {
            continue;
        }

        for (const auto &word : words) {
            if (tmp == word) {
                freqs[tmp]++;
            }
        }

    }

    return freqs;
}

std::unordered_map<std::string, std::vector<std::string>> ByteLevelBPE::initializeSplits(const std::unordered_map<std::string, int> &freqs) {

    std::unordered_map<std::string, std::vector<std::string>> splits;

    for (const auto &freq : freqs) {

        std::string word = freq.first;

        std::vector<std::string> token;

        bool is_tag = (word.size() > 3) && (
                (word.front() == '[' && word.back() == ']') ||
                        (word.front() == '<' && word.back() == '>'));

        if (is_tag) {
            token.push_back(word);
        } else {
            for (char & c : word) {
                std::string single_byte(1, c);
                token.push_back(single_byte);
            }
        }

        splits[word] = std::move(token);

    }

    return splits;

}

std::unordered_map<std::pair<std::string, std::string>, int, PairHash>
        ByteLevelBPE::computePairFreqs(const std::unordered_map<std::string, int> &freqs,
                               const std::unordered_map<std::string, std::vector<std::string>> &splits) {
    std::unordered_map<std::pair<std::string, std::string>, int, PairHash> pair_freqs;

    for (const auto &entry : freqs) {
        const std::string &word = entry.first;
        int word_count = entry.second;

        const auto &tokens = splits.at(word);
        if (tokens.size() < 2) {
            continue;
        }

        for (size_t i =0; i < tokens.size() - 1; ++i) {
            pair_freqs[{tokens[i], tokens[i + 1]}] += word_count;
        }

    }

    return pair_freqs;
}

std::pair<std::string, std::string>
        ByteLevelBPE::findBestPair(const std::unordered_map<std::pair<std::string, std::string>, int, PairHash> &pair_freqs) {

    int max_freq = 0;
    std::pair<std::string, std::string> best_pair;
    for (const auto &pair_freq :pair_freqs) {
        if (max_freq < pair_freq.second) {
            max_freq = pair_freq.second;
            best_pair = pair_freq.first;
        }
    }

    return best_pair;

}

u_int32_t ByteLevelBPE::getUnicodeCodePoint(const std::string &str, size_t pos, size_t len) {
    const auto * s = reinterpret_cast<const unsigned char*>(str.data() + pos);
    if (len == 3) {
        return ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
    } else if (len == 4) {
        return ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
    }
    return 0;
}

bool ByteLevelBPE::isHanzi(uint32_t cp) {
    return (cp >= 0x4E00 && cp <= 0x9FFF) ||
           (cp >= 0x3400 && cp <= 0x4DBF) ||
           (cp >= 0x20000 && cp <= 0x2A6DF);
}