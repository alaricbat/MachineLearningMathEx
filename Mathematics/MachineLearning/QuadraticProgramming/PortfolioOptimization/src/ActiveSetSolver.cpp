#include "../include/ActiveSetSolver.h"
#include "../include/KKTSolver.h"

#include <algorithm>
#include <vector>

std::vector<double> ActiveSetSolver::solve(
        const std::vector<std::vector<double>>& covarianceMatrix,
        const std::vector<std::vector<double>>& activeMatrix,
        const std::vector<double>& bVector,
        std::vector<double>& xVector,
        const std::vector<double>& cVector) {
    std::vector<double> weights = solveWithActiveSet(
                covarianceMatrix,
                activeMatrix,
                bVector,
                xVector,
                cVector);
    return weights;
}

std::vector<double> ActiveSetSolver::solveWithActiveSet(
            const std::vector<std::vector<double>>& covarianceMatrix,
            const std::vector<std::vector<double>>& activeMatrix,
            const std::vector<double>& bVector,
            std::vector<double>& xVector,
            const std::vector<double>& cVector) {
    KKTSolver solver;

    const size_t n = covarianceMatrix.size();

    if (n == 0) return {};
    if (xVector.empty()) return {};

    // Initial working set
    workingSet.push_back(0);
    for (int i = 0; i < n; i++) {
        workingSet.push_back(i + 1);
    }

    std::vector<std::vector<double>> activeMatrix_k;

    // Reserve memory upfront to avoid slow dynamic reallocations
    activeMatrix_k.reserve(workingSet.size());

    for (int activeIdx : workingSet) {
        // Safety check to ensure we do not jump out of bounds
        if (activeIdx >= 0 && activeIdx < static_cast<int>(activeMatrix.size())) {
            activeMatrix_k.push_back(activeMatrix[activeIdx]);
        }
    }

    auto offset = static_cast<std::ptrdiff_t>(xVector.size());
    std::vector<double> kktResult = solver.solve(
                covarianceMatrix,
                activeMatrix_k,
                xVector,
                cVector);
        std::vector<double> dk(kktResult.begin(), kktResult.begin() + offset);
        std::vector<double> lambda_vector(kktResult.begin() + offset, kktResult.end());

    while(isContinue(dk, lambda_vector)) {

        if (allCloseToZero(dk)) {
            bool isLambdaAllPositive = true;
            for (size_t k = 0; k < workingSet.size(); ++k) {
                int constraintIdx = workingSet[k];
                if (constraintIdx == 0) {
                    continue;
                }
                if (lambda_vector[k] < -1e-6) {
                    isLambdaAllPositive = false;
                    break;
                }
            }
            if (isLambdaAllPositive) break;
            else {
                //Find the most negative
                int mostNegativeIdx = -1;
                double mostNegativeVal = 0.0;
                for (size_t k = 0; k < workingSet.size(); ++k) {
                    int constraintIdx = workingSet[k];
                    if (constraintIdx == 0) {
                        continue;
                    }
                    if (lambda_vector[k] < mostNegativeVal) {
                        mostNegativeIdx = constraintIdx;
                        mostNegativeVal = lambda_vector[k];
                    }
                }
                if (mostNegativeIdx != -1) {
                    workingSet.erase(
                            std::remove(workingSet.begin(), workingSet.end(), mostNegativeIdx),
                            workingSet.end()
                            );
                }
            }
        } else {
            double alpha_k = 1.0;
            int constraint_num = -1;
            for (size_t i = 1; i < bVector.size(); ++i) {
                bool isBelongWorkingSet = false;
                for (int workingIdx : workingSet) {
                    if (i == workingIdx) {
                        isBelongWorkingSet = true;
                        break;
                    }
                }
                if (isBelongWorkingSet) continue;
                const std::vector<double>& a_i = activeMatrix[i];
                const double b_i = bVector[i];
                double denominator = 0.0;
                for (size_t j = 0; j < a_i.size(); j++) {
                    denominator += a_i[j] * dk[j];
                }
                double margin = 0.0;
                if (denominator > 1e-6) {
                    for (size_t j = 0; j < a_i.size(); j++) {
                        margin += a_i[j] * xVector[j];
                    }
                    margin = b_i - margin;
                }
                double val = margin / denominator;
                if (val < alpha_k) {
                    alpha_k = val;
                    constraint_num = static_cast<int>(i);
                }
                if (alpha_k < 1.0 && constraint_num != -1) {
                    workingSet.push_back(constraint_num);
                }
            }

            for (size_t j = 0; j < xVector.size(); ++j) {
                xVector[j] = xVector[j] + alpha_k * dk[j];
            }
        }

        // Reserve memory upfront to avoid slow dynamic reallocations
        activeMatrix_k.reserve(workingSet.size());

        for (int activeIdx : workingSet) {
            // Safety check to ensure we do not jump out of bounds
            if (activeIdx >= 0 && activeIdx < static_cast<int>(activeMatrix.size())) {
                activeMatrix_k.push_back(activeMatrix[activeIdx]);
            }
        }

        kktResult = solver.solve(
                covarianceMatrix,
                activeMatrix_k,
                xVector,
                cVector);
        dk.assign(kktResult.begin(), kktResult.begin() + offset);
        lambda_vector.assign(kktResult.begin() + offset, kktResult.end());
    }

    return xVector;
}

bool ActiveSetSolver::allCloseToZero(const std::vector<double>& vec, double atol) {
    return std::all_of(vec.begin(), vec.end(), [atol](double val) {
       return std::abs(val) < atol;
    });
}

bool ActiveSetSolver::isContinue(const std::vector<double>& dk, const std::vector<double>& lambda_vector) {
    bool isAllZero = allCloseToZero(dk);
    bool isLambdaAllPositive = true;

    for (size_t k = 0; k < workingSet.size(); ++k) {
        int constraintIdx = workingSet[k];
        if (constraintIdx == 0) {
            continue;
        }
        if (lambda_vector[k] < -1e-6) {
            isLambdaAllPositive = false;
            break;
        }
    }
    return isLambdaAllPositive || isAllZero;
}