#include "../include/BookDownloader.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <curl/curl.h>

const std::map<std::string, std::string> BookDownloader::DATASOURCE = {
        {"L47181", "L47181"},
        {"L47182", "L47182"},
        {"L47183", "L47183"},
        {"L47184", "L47184"},
        {"M14860", "M14860"}
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
        filenames.push_back("dataset/" + item.first + ".log");
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
