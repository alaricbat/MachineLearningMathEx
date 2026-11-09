#include <iostream>
#include <vector>

class Matrix {

public:

    static std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>> &matrix) {

        if (matrix.empty() || matrix[0].empty()) {
            return {};
        }

        int n = static_cast<int>(matrix.size());
        int m = static_cast<int>(matrix[0].size());
        std::vector<std::vector<double>> matrix_t(m);

        for (int i = 0; i < m; i++) {
            std::vector<double> cols(n);
            for (int j = 0; j < n; j++) {
                cols[j] = matrix[j][i];
            }
            matrix_t[i] = cols;
        }

        return matrix_t;

    }

    static std::vector<std::vector<double>> dot(const std::vector<std::vector<double>> &a
                                                , const std::vector<std::vector<double>> &b) {

        const int row_num = static_cast<int>(a.size());
        const int col_num = static_cast<int>(b[0].size());

        const int a_cols = static_cast<int>(a[0].size());

        std::vector<std::vector<double>> result(row_num);

        for (size_t a_i = 0; a_i < row_num; a_i++) {
            std::vector<double> result_cols(col_num);
            for (size_t b_j = 0; b_j < col_num; b_j++) {
                double result_col = 0.0;
                for (size_t a_j = 0; a_j < a_cols; a_j++) {
                    double a_ij = a[a_i][a_j];
                    result_col += a_ij * b[a_j][b_j];
                }
                result_cols[b_j] = result_col;
            }
            result[a_i] = result_cols;
        }

        return result;
    }

};