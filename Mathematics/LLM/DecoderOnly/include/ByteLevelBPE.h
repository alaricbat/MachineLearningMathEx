#ifndef MACHINELEARNINGMATHEX_BYTELEVELBPE_H
#define MACHINELEARNINGMATHEX_BYTELEVELBPE_H

#include <iostream>
#include <vector>

struct PairHash {
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
    }
};

class ByteLevelBPE {

public:

    static std::vector<std::string> split(std::string &dataset);

private:

    static u_int32_t getUnicodeCodePoint(const std::string& str, size_t pos, size_t len);
    static bool isHanzi (uint32_t cp);

};

#endif //MACHINELEARNINGMATHEX_BYTELEVELBPE_H
