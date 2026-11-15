#include "../include/Gutenberg.h"
#include "../include/BookDownloader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <experimental/string_view>
#include <algorithm>

std::string Gutenberg::preprocess(const std::string &filename) {

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[Gutenberg][preprocess]: Failed to open file for preprocessing: " << filename << '\n';
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    std::string clean_text;
    clean_text.reserve(text.size());

    std::experimental::string_view sv(text);
    size_t pos = 0;

    while (pos < sv.size()) {
        size_t next_newline = sv.find('\n', pos);
        std::experimental::string_view line = (next_newline == std::experimental::string_view::npos)
                                ? sv.substr(pos)
                                : sv.substr(pos, next_newline - pos + 1);

        bool is_empty = std::all_of(line.begin(), line.end(), [](unsigned char ch) {
            return std::isspace(ch);
        });

        if (!is_empty) {
            clean_text.append(line.data(), line.size());
        }

        if (next_newline == std::experimental::string_view::npos) {
            break;
        }
        pos = next_newline + 1;
    }

    return clean_text;
}

std::vector<std::string> Gutenberg::getDatasetText() {

    std::vector<std::string> final;
    std::vector<std::string> dataset = BookDownloader::getFilenames();

    for (const auto &data : dataset) {
        std::string content = preprocess(data);
        final.push_back(content);
    }

    return final;

}