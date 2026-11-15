#include "include/BookDownloader.h"
#include "include/ByteLevelBPE.h"
#include "include/Gutenberg.h"

int main() {

    std::vector<std::string> dataset = Gutenberg::getDatasetText();
    std::cout << "Dataset size: " << dataset.size() << std::endl;
    std::vector<std::string> splits = ByteLevelBPE::split(dataset[0]);

    return 0;
}
