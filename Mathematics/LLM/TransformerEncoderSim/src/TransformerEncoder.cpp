#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

#include "../utils/Constant.cpp"

class TransformerEncoder {

public:

    static std::vector<std::vector<double>> encode(const std::vector<std::string> &tokens) {
        std::vector<std::vector<double>> H(tokens.size());
        for (size_t i = 0; i < tokens.size(); ++i) {
            std::vector<double> h(Constants::EMBED_DIM);
            for (size_t j = 0; j < Constants::EMBED_DIM; ++j) {
                h[j] = (sin(static_cast<double >(tokens[i].size()) + Constants::EMBED_DIM));
            }
            H[i] = h;
        }
        return H;
    }

};
