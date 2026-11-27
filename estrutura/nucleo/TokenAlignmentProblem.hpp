#ifndef ESTRUTURA_NUCLEO_TOKEN_ALIGNMENT_PROBLEM_H
#define ESTRUTURA_NUCLEO_TOKEN_ALIGNMENT_PROBLEM_H

#include <string>
#include <vector>

#include "estrutura/alinhamento/IAlignmentProblem.hpp"

namespace estrutura::nucleo {
    class TokenAlignmentProblem : public alinhamento::IAlignmentProblem {
        std::vector<std::string> before;

        std::vector<std::string> after;

        int mismatchCost;

        int unmatchedCost;

    public:
        TokenAlignmentProblem(const std::vector<std::string> &before, const std::vector<std::string> &after,
                              int mismatchCost, int unmatchedCost);

        [[nodiscard]] static TokenAlignmentProblem forLines(const std::vector<std::string> &before,
                                                            const std::vector<std::string> &after);

        [[nodiscard]] static TokenAlignmentProblem forWords(const std::vector<std::string> &before,
                                                            const std::vector<std::string> &after);

        [[nodiscard]] int lengthX() const override;

        [[nodiscard]] int lengthY() const override;

        [[nodiscard]] int pairCost(int xIndex, int yIndex) const override;

        [[nodiscard]] int unmatchedXCost(int xIndex) const override;

        [[nodiscard]] int unmatchedYCost(int yIndex) const override;
    };
} // namespace estrutura::nucleo
#endif