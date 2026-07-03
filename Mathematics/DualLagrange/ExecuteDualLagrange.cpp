/**
 * ============================================================================
 * 📝 PRACTICAL CASE STUDY: MARKETING BUDGET ALLOCATION FOR A FINTECH APP
 * 💡 KNOWLEDGE REPOSITORY: MULTI-CONSTRAINT LAGRANGE DUALITY
 * ============================================================================
 * * --- 1. PROBLEM STATEMENT (PRIMAL FORMULATION) ---
 * Suppose you have a total budget of $10,000 (normalized to 10 capital units)
 * to allocate across 3 marketing channels to acquire users for a Fintech App:
 * - Channel 1 (x1): Facebook/Google Search Ads (Mass market acquisition)
 * - Channel 2 (x2): Financial/Economic KOLs (High-quality, niche users)
 * - Channel 3 (x3): Affiliate Marketing (Performance-based networks)
 * * Objective Function:
 * We model the inefficiency risk or opportunity cost as a non-linear quadratic function.
 * We want to minimize this risk across all channels:
 * Minimize: f(x1, x2, x3) = x1^2 + x2^2 + x3^2
 * * System of 2 Constraints:
 * - Constraint 1 (Total Budget): The sum of all budgets must equal exactly 10 units.
 * x1 + x2 + x3 = 10  ==>  10 - x1 - x2 - x3 = 0
 * - Constraint 2 (Strategic Rule): CMO requires Facebook (x1) to outspend KOLs (x2)
 * by exactly 2 units to maintain baseline brand visibility.
 * x1 - x2 = 2        ==>  2 - x1 + x2 = 0
 * * * --- 2. MATHEMATICAL SETUP (LAGRANGE DUALITY) ---
 * Step 1: Formulate the Primal Lagrangian Function L(x1, x2, x3, lambda, mu)
 * We inject both constraints into the objective function using two distinct dual variables
 * (Lagrange Multipliers): lambda (for budget) and mu (for strategy).
 * L = x1^2 + x2^2 + x3^2 + lambda*(10 - x1 - x2 - x3) + mu*(2 - x1 + x2)
 * * Step 2: Minimize the Primal Variables analytically by setting partial derivatives to 0:
 * dL/dx1 = 2*x1 - lambda - mu = 0  ==>  x1 = (lambda + mu) / 2
 * dL/dx2 = 2*x2 - lambda + mu = 0  ==>  x2 = (lambda - mu) / 2
 * dL/dx3 = 2*x3 - lambda      = 0  ==>  x3 = lambda / 2
 * * Step 3: Derive the Lagrange Dual Function g(lambda, mu)
 * Substitute x1, x2, x3 back into L to completely eliminate the primal variables:
 * g(lambda, mu) = -0.75 * lambda^2 - 0.5 * mu^2 + 10 * lambda + 2 * mu
 * * Step 4: Maximize the Dual Function (Dual Problem)
 * Instead of solving a constrained 3D problem, we solve an UNCONSTRAINED 2D maximization problem:
 * Maximize: g(lambda, mu) over the dual space.
 * * * --- 3. CORE INSIGHT ---
 * - Each constraint adds exactly ONE dimension to the dual space.
 * - The primal variables (x1, x2, x3) are completely isolated from the search loop.
 * Once the "optimal shadow prices" (lambda*, mu*) are found at the peak of the dual hill,
 * the physical real-world allocations instantly unlock.
 */

#include <iostream>
#include <cmath>
#include <iomanip>

double dualFunction(double lambda, double mu) {
    return -0.75 * pow(lambda, 2.0) - 0.5 * pow(mu, 2) + 10.0 * lambda + 2.0 * mu;
}

double getGradientLambda(double lambda) {
    return -1.5 * lambda + 10.0;
}

double getGradientMu(double mu) {
    return -1 * mu + 2.0;
}

int main() {

    std::cout<< "=======================================================\n";
    std::cout << "    2-CONSTRAINT LAGRANGE DUAL NUMERICAL SCANNER       \n";
    std::cout<< "=======================================================\n\n";

    double lambda = 0.0;
    double mu = 0.0;

    double learningRate = 0.1;
    double epochs = 100;
    double tolerance = 1e-6; // Early Stopping

    for (int epoch = 1; epoch <= epochs; ++epoch) {

        double gradLambda = getGradientLambda(lambda);
        double gradMu = getGradientMu(mu);

        double nextLambda = lambda + learningRate * gradLambda;
        double nextMu = mu + learningRate * gradMu;

        if (epoch == 1 || epoch % 10 == 0) {
            std::cout << epoch << "\t| " << lambda << "\t| " << mu << "\t| " << dualFunction(lambda, mu) << "\n";
        }

        lambda = nextLambda;
        mu = nextMu;

        if (std::abs(nextLambda - lambda) < tolerance && std::abs(nextMu - mu) < tolerance) {
            std::cout << "... Converged early at epoch " << epoch << "!\n";
            break;
        }
    }

    std::cout << "-------------------------------------------------------\n\n";

    double x1 = (lambda + mu) / 2.0;
    double x2 = (lambda - mu) / 2.0;
    double x3 = lambda / 2.0;

    std::cout << std::setprecision(3) << std::fixed;
    std::cout << "1. Optimal Dual Multipliers Found:\n";
    std::cout << "   -> Optimal Lambda (Budget Tightness) = " << lambda << "\n";
    std::cout << "   -> Optimal Mu (Strategy Tightness)  = " << mu << "\n";

    std::cout << "2. Reconstructed Budget Allocations:\n";
    std::cout << "   => x1 (Facebook/Google Ads) = $" << x1 * 1000 << " (" << x1 << " units)\n";
    std::cout << "   => x2 (KOLs Marketing)      = $" << x2 * 1000 << " (" << x2 << " units)\n";
    std::cout << "   => x3 (Affiliate Marketing)   = $" << x3 * 1000 << " (" << x3 << " units)\n\n";

    std::cout << "3. Verification against Both Constraints:\n";
    std::cout << "   * Constraint 1 (x1 + x2 + x3 = 10) : " << (x1 + x2 + x3) << " units\n";
    std::cout << "   * Constraint 2 (x1 - x2 = 2)       : " << (x1 - x2) << " units\n";
    std::cout << "=======================================================\n";

    return 0;
}
