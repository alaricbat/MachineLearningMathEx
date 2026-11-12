#include "include/BookDownloader.h"
#include "include/Gutenberg.h"

int main() {

    std::vector<std::string> dataset = Gutenberg::getDatasetText();

    return 0;
}
