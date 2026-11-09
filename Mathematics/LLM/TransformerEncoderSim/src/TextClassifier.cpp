#include <iomanip>
#include <vector>

#include "../utils/Matrix.cpp"

class TextClassifier {

private:

    std::vector<std::vector<double>> W;


public:

    TextClassifier() {
        W = {
            {0.8,  1.2, -0.5,  0.9},
            {-1.1, -0.4,  1.5, -0.8},
            {0.1, -0.2,  0.1, -0.1}
        };
    }

    std::vector<double> softmax(std::vector<std::vector<double>> encoder) {

        std::vector<std::vector<double>> encoder_t = Matrix::transpose(W);




    }


};