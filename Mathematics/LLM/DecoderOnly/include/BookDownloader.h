#include <iostream>
#include <vector>
#include <map>

#ifndef MACHINELEARNINGMATHEX_BOOKDOWNLOADER_H
#define MACHINELEARNINGMATHEX_BOOKDOWNLOADER_H

class BookDownloader {
public:
    BookDownloader() = default;
    ~BookDownloader() = default;

    static void downloadAll();
    static bool download(const std::string &url, const std::string &file_path);
    static std::vector<std::string> getFilenames();

private:
    static const std::map<std::string, std::string> DATASOURCE;
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
};


#endif //MACHINELEARNINGMATHEX_BOOKDOWNLOADER_H
