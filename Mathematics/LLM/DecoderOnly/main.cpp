#include "include/BookDownloader.h"
#include "include/ByteLevelBPE.h"
#include "include/Gutenberg.h"

int main() {

    std::vector<std::string> dataset = Gutenberg::getDatasetText();
    std::cout << "Dataset size: " << dataset.size() << std::endl;
    std::vector<std::string> splits = ByteLevelBPE::split(dataset[0]);
    std::unordered_map<std::string, int> freqs = ByteLevelBPE::computeWordFreqs(splits);
    std::unordered_map<std::string, std::vector<std::string>> split = ByteLevelBPE::initializeSplits(freqs);
    std::unordered_map<std::pair<std::string, std::string>, int, PairHash> pair_map = ByteLevelBPE::computePairFreqs(freqs, split);
    std::pair<std::string, std::string> findBestPair = ByteLevelBPE::findBestPair(pair_map);

    return 0;
}
