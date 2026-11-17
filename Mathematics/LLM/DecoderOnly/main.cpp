#include "include/BookDownloader.h"
#include "include/ByteLevelBPE.h"
#include "include/Gutenberg.h"

int main() {

    std::vector<std::string> dataset = Gutenberg::getDatasetText();
    std::vector<std::string> vocab = ByteLevelBPE::train(dataset);

    return 0;
}
