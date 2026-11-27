#include "TokenAlignmentProblem.hpp"

namespace estrutura::nucleo {
    namespace {
        constexpr int lineMismatchCost = 3;
        constexpr int lineUnmatchedCost = 1;
        constexpr int wordMismatchCost = 1;
        constexpr int wordUnmatchedCost = 1;
    }

    TokenAlignmentProblem::TokenAlignmentProblem(const std::vector<std::string> &before,
                                                 const std::vector<std::string> &after, const int mismatchCost,
                                                 const int unmatchedCost)
        : before(before), after(after), mismatchCost(mismatchCost), unmatchedCost(unmatchedCost) {
    }

    TokenAlignmentProblem TokenAlignmentProblem::forLines(const std::vector<std::string> &before,
                                                          const std::vector<std::string> &after) {
        return {before, after, lineMismatchCost, lineUnmatchedCost};
    }

    TokenAlignmentProblem TokenAlignmentProblem::forWords(const std::vector<std::string> &before,
                                                          const std::vector<std::string> &after) {
        return {before, after, wordMismatchCost, wordUnmatchedCost};
    }

    int TokenAlignmentProblem::lengthX() const { return static_cast<int>(before.size()); }

    int TokenAlignmentProblem::lengthY() const { return static_cast<int>(after.size()); }

    int TokenAlignmentProblem::pairCost(const int xIndex, const int yIndex) const {
        return before.at(xIndex) == after.at(yIndex) ? 0 : mismatchCost;
    }

    int TokenAlignmentProblem::unmatchedXCost(const int) const { return unmatchedCost; }

    int TokenAlignmentProblem::unmatchedYCost(const int) const { return unmatchedCost; }
} // namespace estrutura::nucleo