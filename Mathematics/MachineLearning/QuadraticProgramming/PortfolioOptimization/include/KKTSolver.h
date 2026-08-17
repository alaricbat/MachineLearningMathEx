#pragma once

#include "vector"

class KKTSolver {
public:
    /**
     * Solve KKT System, applied active set
     *
     * Return:
     *      Optimal portfolio weights.
     */
     std::vector<double> solve(const std::vector<std::vector<double>>& covarianceMatrix,
                               const std::vector<std::vector<double>>& activeMatrix,
                               const std::vector<double>& xVector,
                               const std::vector<double>& cVector);
private:
    /**
     * Build KKT matrix.
     *
     *      [ Σ   Aᵀ]
     *      [A  0 ]
     */
    std::vector<std::vector<double>> buildKKTMatrix(
            const std::vector<std::vector<double>>& covarianceMatrix,
            const std::vector<std::vector<double>>& activeMatrix);

    /**
     * Build RHS vector.
     *      [-g]
     *      [0]
     */
    std::vector<double> buildRightHandSide(
            const std::vector<std::vector<double>>& covarianceMatrix,
            const std::vector<std::vector<double>>& activeMatrix,
            const std::vector<double>& xVector,
            const std::vector<double>& cVector);
};