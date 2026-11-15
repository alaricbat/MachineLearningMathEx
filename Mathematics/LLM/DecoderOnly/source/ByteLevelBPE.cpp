#include "../include/ByteLevelBPE.h"

#include <sstream>

std::vector<std::string> ByteLevelBPE::split(std::string &dataset) {

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

    for (const std::string &content : arr) {
        std::cout << content << std::endl;
    }

    return arr;

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