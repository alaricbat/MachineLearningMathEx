#include "../include/BookDownloader.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <curl/curl.h>

const std::map<std::string, std::string> BookDownloader::DATASOURCE = {
        {"moby_dick", "https://www.gutenberg.org/ebooks/2701.txt.utf-8"},
        {"frankenstein", "https://www.gutenberg.org/ebooks/84.txt.utf-8"},
        {"dracula", "https://www.gutenberg.org/ebooks/345.txt.utf-8"},
        {"little_women", "https://www.gutenberg.org/ebooks/37106.txt.utf-8"},
        {"pride_and_prejudice", "https://www.gutenberg.org/ebooks/1342.txt.utf-8"},
        {"alice_in_wonderland", "https://www.gutenberg.org/ebooks/11.txt.utf-8"},
        {"crime_and_punishment", "https://www.gutenberg.org/ebooks/2554.txt.utf-8"},
        {"tom_sawyer", "https://www.gutenberg.org/ebooks/74.txt.utf-8"},
        {"tale_of_two_cities", "https://www.gutenberg.org/ebooks/98.txt.utf-8"},
        {"sherlock_holmes", "https://www.gutenberg.org/ebooks/1661.txt.utf-8"},
        {"war_and_peace", "https://www.gutenberg.org/ebooks/2600.txt.utf-8"}
};

static bool fileExists(const std::string& filepath) {
    std::ifstream ifs(filepath);
    return ifs.good();
}

static void ensureDirectoryExists(const std::string& dirPath) {
    mkdir(dirPath.c_str(), 0755);
}

size_t BookDownloader::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    auto* ofs = static_cast<std::ofstream*>(userp);
    ofs->write(static_cast<const char*>(contents), static_cast<std::streamsize>(totalSize));
    return totalSize;
}

std::vector<std::string> BookDownloader::getFilenames() {

    std::vector<std::string> filenames;

    for (const auto &item : DATASOURCE) {
        filenames.push_back("dataset/" + item.first + ".txt");
    }

    return filenames;
}

bool BookDownloader::download(const std::string &url, const std::string &file_path) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::ofstream ofs(file_path, std::ios::binary);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file: " << file_path << '\n';
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);

    CURLcode res = curl_easy_perform(curl);
    bool success = (res == CURLE_OK);
    if (!success) {
        std::cerr << "Download failed (" << file_path << "): " << curl_easy_strerror(res) << '\n';
    }

    curl_easy_cleanup(curl);
    return success;
}

void BookDownloader::downloadAll() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    ensureDirectoryExists("dataset");

    for (const auto &item : DATASOURCE) {
        const std::string &filename = item.first;
        const std::string &url = item.second;
        std::string filepath = "dataset/" + filename + ".txt";

        if (!fileExists(filepath)) {
            std::cout << "Downloading " << filepath << "...\n";
            download(url, filepath);
        } else {
            std::cout << filepath << " already exists, skipping.\n";
        }
    }

    curl_global_cleanup();
}
