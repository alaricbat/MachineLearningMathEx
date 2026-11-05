#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

const int EMBED_DIM = 4;

class TransformerEncoder {

public:

    static std::vector<std::vector<double>> encode(const std::vector<std::string> &tokens) {
        std::vector<std::vector<double>> H(tokens.size());
        for (size_t i = 0; i < tokens.size(); ++i) {
            std::vector<double> h(EMBED_DIM);
            for (size_t j = 0; j < EMBED_DIM; ++j) {
                h[j] = (sin(static_cast<double >(tokens[i].size()) + EMBED_DIM));
            }
            H[i] = h;
        }
        return H;
    }

};
