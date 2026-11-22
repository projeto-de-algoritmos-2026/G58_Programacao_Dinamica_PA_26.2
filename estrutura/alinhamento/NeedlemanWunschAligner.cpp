#include "NeedlemanWunschAligner.hpp"

#include <algorithm>

namespace estrutura::alinhamento {
    namespace {
        class CandidateCosts {
            const IAlignmentProblem &problem;
            const CostTable &costTable;

        public:
            CandidateCosts(const IAlignmentProblem &problem, const CostTable &costTable) : problem(problem),
                costTable(costTable) {
            }

            [[nodiscard]] int costIfPaired(const int xPrefixLength, const int yPrefixLength) const {
                return costTable.at(xPrefixLength - 1, yPrefixLength - 1) + problem.pairCost(
                           xPrefixLength - 1, yPrefixLength - 1);
            }

            [[nodiscard]] int costIfXUnmatched(const int xPrefixLength, const int yPrefixLength) const {
                return costTable.at(xPrefixLength - 1, yPrefixLength) + problem.unmatchedXCost(xPrefixLength - 1);
            }

            [[nodiscard]] int costIfYUnmatched(const int xPrefixLength, const int yPrefixLength) const {
                return costTable.at(xPrefixLength, yPrefixLength - 1) + problem.unmatchedYCost(yPrefixLength - 1);
            }

            [[nodiscard]] bool cameFromPair(const int xPrefixLength, const int yPrefixLength) const {
                return xPrefixLength > 0 && yPrefixLength > 0 && costTable.at(xPrefixLength, yPrefixLength) ==
                       costIfPaired(xPrefixLength, yPrefixLength);
            }

            [[nodiscard]] bool cameFromXUnmatched(const int xPrefixLength, const int yPrefixLength) const {
                return xPrefixLength > 0 && costTable.at(xPrefixLength, yPrefixLength) == costIfXUnmatched(
                           xPrefixLength, yPrefixLength);
            }
        };
    }

    Alignment NeedlemanWunschAligner::align(const IAlignmentProblem &problem) const {
        const CostTable costTable = fillTable(problem);

        Alignment alignment;
        alignment.cost = costTable.at(problem.lengthX(), problem.lengthY());

        alignment.columns = traceback(problem, costTable);

        return alignment;
    }

    CostTable NeedlemanWunschAligner::fillTable(const IAlignmentProblem &problem) {
        const int lengthX = problem.lengthX();
        const int lengthY = problem.lengthY();

        CostTable costTable(lengthX, lengthY);

        const CandidateCosts candidates(problem, costTable);

        for (int xPrefixLength = 1; xPrefixLength <= lengthX; xPrefixLength++) {
            costTable.at(xPrefixLength, 0) = candidates.costIfXUnmatched(xPrefixLength, 0);
        }

        for (int yPrefixLength = 1; yPrefixLength <= lengthY; yPrefixLength++) {
            costTable.at(0, yPrefixLength) = candidates.costIfYUnmatched(0, yPrefixLength);
        }

        for (int xPrefixLength = 1; xPrefixLength <= lengthX; xPrefixLength++) {
            for (int yPrefixLength = 1; yPrefixLength <= lengthY; yPrefixLength++) {
                costTable.at(xPrefixLength, yPrefixLength) = std::min({
                    candidates.costIfPaired(xPrefixLength, yPrefixLength),
                    candidates.costIfXUnmatched(xPrefixLength, yPrefixLength),
                    candidates.costIfYUnmatched(xPrefixLength, yPrefixLength)
                });
            }
        }

        return costTable;
    }

    std::vector<AlignmentColumn> NeedlemanWunschAligner::traceback(const IAlignmentProblem &problem,
                                                                   const CostTable &costTable) {
        int xPrefixLength = problem.lengthX();
        int yPrefixLength = problem.lengthY();

        const CandidateCosts candidates(problem, costTable);

        std::vector<AlignmentColumn> columns;

        while (xPrefixLength > 0 || yPrefixLength > 0) {
            if (candidates.cameFromPair(xPrefixLength, yPrefixLength)) {
                columns.push_back({xPrefixLength - 1, yPrefixLength - 1});
                xPrefixLength--;
                yPrefixLength--;
            } else if (candidates.cameFromXUnmatched(xPrefixLength, yPrefixLength)) {
                columns.push_back({xPrefixLength - 1, std::nullopt});
                xPrefixLength--;
            } else {
                columns.push_back({std::nullopt, yPrefixLength - 1});
                yPrefixLength--;
            }
        }

        std::reverse(columns.begin(), columns.end());

        return columns;
    }
} // namespace estrutura::alinhamento
