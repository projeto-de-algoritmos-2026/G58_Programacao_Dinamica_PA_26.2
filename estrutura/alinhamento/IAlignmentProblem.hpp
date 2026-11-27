#ifndef ESTRUTURA_ALINHAMENTO_I_ALIGNMENT_PROBLEM_H
#define ESTRUTURA_ALINHAMENTO_I_ALIGNMENT_PROBLEM_H


namespace estrutura::alinhamento {
    class IAlignmentProblem {
    public:
        virtual ~IAlignmentProblem() = default;

        [[nodiscard]] virtual int lengthX() const = 0;

        [[nodiscard]] virtual int lengthY() const = 0;

        [[nodiscard]] virtual int pairCost(int xIndex, int yIndex) const = 0;

        [[nodiscard]] virtual int unmatchedXCost(int xIndex) const = 0;

        [[nodiscard]] virtual int unmatchedYCost(int yIndex) const = 0;
    };
} // namespace estrutura::alinhamento
#endif