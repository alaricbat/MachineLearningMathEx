
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
            {1, 1,  1},
            {1, 1,  1}
    };
    std::vector<std::vector<double>> b = {
            {2, 2},
            {2, 2},
            {2, 2}
    };

    std::vector<std::vector<double>> multiplier =  Matrix::dot(a, b);

    for (const std::vector<double> &vectors : multiplier) {
        std::cout << "[ ";
        for (const double &number : vectors) {
            std::cout << number << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}