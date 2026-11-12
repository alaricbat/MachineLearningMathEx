#include "../include/Gutenberg.h"
#include "../include/BookDownloader.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::string Gutenberg::trim(const std::string& str) {

    const std::string whitespace = " \t\n\r\f\v";

    size_t first = str.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }

    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

std::string Gutenberg::preprocess(const std::string &filename) {

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[Gutenberg][preprocess]: Failed to open file for preprocessing: " << filename << '\n';
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    const std::string startMarker = "*** START OF THE PROJECT GUTENBERG EBOOK";
    const std::string endMarker = "*** END OF THE PROJECT GUTENBERG EBOOK";

    size_t start = text.find(startMarker);
    if (start != std::string::npos) {
        size_t newlinePos = text.find('\n', start);
        if (newlinePos != std::string::npos) {
            start = newlinePos + 1;
        }
    } else {
        start = 0;
    }

    size_t end = text.find(endMarker, start);
    if (end == std::string::npos) {
        end = text.length();
    }

    std::string mainContent = trim(text.substr(start, end - start));

    std::istringstream lineStream(mainContent);
    std::string line;
    std::string result;

    result.reserve(mainContent.size());

    bool isFirstLine = true;
    while (std::getline(lineStream, line)) {
        std::string cleanedLine = trim(line);
        if (!cleanedLine.empty()) {
            if (!isFirstLine) {
                result += '\n';
            }
            result += cleanedLine;
            isFirstLine = false;
        }
    }

    return result;
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