#ifndef ESTRUTURA_ALINHAMENTO_SUB_PROBLEM_H
#define ESTRUTURA_ALINHAMENTO_SUB_PROBLEM_H

#include "estrutura/alinhamento/IAlignmentProblem.hpp"
#include "estrutura/alinhamento/IndexRange.hpp"

namespace estrutura::alinhamento {
    class SubProblem : public IAlignmentProblem {
        const IAlignmentProblem &whole;

        IndexRange xRange;

        IndexRange yRange;

    public:
        SubProblem(const IAlignmentProblem &whole, IndexRange xRange, IndexRange yRange);

        [[nodiscard]] const IAlignmentProblem &wholeProblem() const;

        [[nodiscard]] IndexRange rangeX() const;

        [[nodiscard]] IndexRange rangeY() const;

        [[nodiscard]] int lengthX() const override;

        [[nodiscard]] int lengthY() const override;

        [[nodiscard]] int pairCost(int xIndex, int yIndex) const override;

        [[nodiscard]] int unmatchedXCost(int xIndex) const override;

        [[nodiscard]] int unmatchedYCost(int yIndex) const override;
    };
} // namespace estrutura::alinhamento
#endif