#ifndef MACHINELEARNINGMATHEX_BYTELEVELBPE_H
#define MACHINELEARNINGMATHEX_BYTELEVELBPE_H

#include <iostream>
#include <vector>
#include <unordered_map>

struct PairHash {
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        // Combine two hashes using the Boost hash_combine formula to break symmetry
        // and prevent collisions (e.g., ("A", "B") vs ("B", "A"), or ("A", "A") -> 0).
        // 0x9E3779B9 (2654435769) is derived from the golden ratio for uniform bit distribution.
        //
        // Example (assuming h1 = 100, h2 = 200):
        //   Pair("A", "B"): 100 ^ (200 + 2654435769 + (100 << 6) + (100 >> 2)) = 2654442494
        //   Pair("B", "A"): 200 ^ (100 + 2654435769 + (200 << 6) + (200 >> 2)) = 2654448519
        return h1 ^ (h2 + 0x9E3779B9 + (h1 << 6) + (h1 >> 2));
    }
};

class ByteLevelBPE {

public:

    static std::vector<std::string> split(const std::string &dataset);
    static std::unordered_map<std::string, int> computeWordFreqs(const std::vector<std::string> &words);
    static std::unordered_map<std::string, std::vector<std::string>> initializeSplits(const std::unordered_map<std::string, int> &freqs);
    static std::unordered_map<std::pair<std::string, std::string>, int, PairHash> computePairFreqs(
            const std::unordered_map<std::string, int> &freqs,
            const std::unordered_map<std::string, std::vector<std::string>> &splits);
    static std::pair<std::string, std::string> findBestPair(const std::unordered_map<std::pair<std::string, std::string>, int, PairHash> &pair_freqs);
    static std::string mergeBestPair(const std::pair<std::string, std::string> &best_pair);
    static std::vector<std::string> train(const std::vector<std::string> &dataset);

private:

    static u_int32_t getUnicodeCodePoint(const std::string& str, size_t pos, size_t len);
    static bool isHanzi(uint32_t cp);

};

#endif //MACHINELEARNINGMATHEX_BYTELEVELBPE_H
