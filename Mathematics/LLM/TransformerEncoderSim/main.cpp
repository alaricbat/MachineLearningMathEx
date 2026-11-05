
#include "src/PretrainedNLPModel.cpp"
#include "src/TransformerEncoder.cpp"

#include <iomanip>
#include <iostream>

int main() {

    std::vector<std::string> tokens = PretrainedNLPModel::tokenize("I love the food here. It’s amazing!");
    std::vector<std::vector<double>> encoders = TransformerEncoder::encode(tokens);

    for (const std::vector<double> &vectors : encoders) {
        std::cout << "[ ";
        for (const double &number : vectors) {
            std::cout << number << " ";
        }
        std::cout << " ]" << std::endl;
    }

    return 0;
}