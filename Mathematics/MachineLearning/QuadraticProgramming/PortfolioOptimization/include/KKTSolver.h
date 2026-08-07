#pragma once

#include "vector"

class KKTSolver {
public:
    /**
     * Solve KKT System
     *
     * Return:
     *      Optimal portfolio weights.
     */
     std::vector<double> solve(const std::vector<std::vector<double>>& covarianceMatrix);
private:
    /**
     * Build KKT matrix.
     *
     *      [ Σ   1 ]
     *      [1ᵀ  0 ]
     */
    std::vector<std::vector<double>> buildKKTMatrix(
            const std::vector<std::vector<double>>& covarianceMatrix);

    /**
     * Build RHS vector.
     *
     *      [0]
     *      [0]
     *      ...
     *      [1]
     */
    std::vector<double> buildRightHandSide(size_t numberOfAssets);
};