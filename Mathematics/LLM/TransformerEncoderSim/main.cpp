
#include "src/PretrainedNLPModel.cpp"
#include "src/TransformerEncoder.cpp"
#include "src/TextClassifier.cpp"

#include <iomanip>
#include <iostream>

int main() {

    std::vector<std::string> tokens = PretrainedNLPModel::tokenize("I love the food here. It’s amazing!");
    std::vector<std::vector<double>> encoders = TransformerEncoder::encode(tokens);
    std::vector<std::vector<double>> a = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
    };
    std::vector<std::vector<double>> b = {
            {2, 2},
            {2, 2},
            {2, 2}
    };

    std::vector<double> probs =  TextClassifier::predict(encoders);

    std::vector<std::string> labels = {"positive", "negative", "neutral"};
    std::cout << "=== CLASSIFICATION RESULT ===\n";
    size_t max_idx = 0;
    for (size_t i = 0; i < probs.size(); ++i) {
        std::cout << "  - Pr(" << std::left << std::setw(8) << labels[i] << ") = "
                  << std::fixed << std::setprecision(4) << probs[i] << "\n";
        if (probs[i] > probs[max_idx]) {
            max_idx = i;
        }
    }

    std::cout << "\n=> (Predicted Label): " << labels[max_idx] << std::endl;

    return 0;
}