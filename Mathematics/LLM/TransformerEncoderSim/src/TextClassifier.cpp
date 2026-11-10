#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../utils/Matrix.cpp"
#include "../utils/Constant.cpp"

class TextClassifier {

private:

    static std::vector<std::vector<double>> W;

    static std::vector<double> softmax(const std::vector<double> &logits) {

        std::vector<double> probs(Constants::NUM_CLASSES, 0.0);

        double max_val = *std::max_element(logits.begin(), logits.end());

        double sum = 0.0;
        for (const auto &val: logits) {
            sum += std::exp(val - max_val);
        }

        for (size_t i  = 0; i < Constants::NUM_CLASSES; ++i) {
            probs[i] = std::exp(logits[i] - max_val) / sum;
        }

        return probs;

    }


public:

    static std::vector<double> predict(const std::vector<std::vector<double>> &encoders) {

        std::vector<double> pools(Constants::EMBED_DIM, 0.0);

        for (const std::vector<double> &encoder : encoders) {
            for (size_t i = 0; i < Constants::EMBED_DIM; ++i) {
                pools[i] += encoder[i];
            }
        }

        for (size_t i = 0; i < Constants::EMBED_DIM; ++i) {
            pools[i] /= (double ) encoders.size();
        }

        std::vector<std::vector<double>> final_pools(1, pools);

        std::vector<std::vector<double>> W_t = Matrix::transpose(W);
        std::vector<std::vector<double>> logits = Matrix::dot(final_pools, W_t);

        return softmax(logits[0]);

    }

};

std::vector<std::vector<double>> TextClassifier::W = {
        {0.8, 1.2, -0.5, 0.9},
        {-1.1, -0.4, 1.5, -0.8},
        {0.1, -0.2, 0.1, -0.1}
};