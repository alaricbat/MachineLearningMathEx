#pragma once

#include "vector"

class ActiveSetSolver {

public:
    std::vector<double> solve(
            const std::vector<std::vector<double>>& covarianceMatrix,
            const std::vector<std::vector<double>>& activeMatrix,
            const std::vector<double>& bVector,
            std::vector<double>& xVector,
            const std::vector<double>& cVector);

private:

    // Indicates which constraints are currently active in the working set
    std::vector<int>  workingSet;

    /**
     * @brief Solves a Quadratic Programming (QP) subproblem based on the current active set.
     *
     * @param covarianceMatrix The objective function's quadratic matrix (Q).
     * @param constraintMatrix The matrix representing the linear constraints (A).
     * @param boundaryVector   The right-hand side vector of the constraints (b).
     * @return std::vector<double> The solved primal variables or Lagrange multipliers.
     */
    std::vector<double> solveWithActiveSet(
            const std::vector<std::vector<double>>& covarianceMatrix,
            const std::vector<std::vector<double>>& activeMatrix,
            const std::vector<double>& bVector,
            std::vector<double>& xVector,
            const std::vector<double>& cVector);

    /**
     * @brief Checks if all elements in a vector are close to zero within an absolute tolerance.
     *        Equivalent to np.allclose(vec, 0.0, atol=tol)
     */
    bool allCloseToZero(const std::vector<double>& vec, double atol = 1e-6);

    bool isContinue(const std::vector<double>& dk, const std::vector<double>& lambda_vector);

};