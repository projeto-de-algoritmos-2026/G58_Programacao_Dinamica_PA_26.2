#ifndef PROGRAMACAO_DINAMICA_G58_STRINGPROBLEM_HPP
#define PROGRAMACAO_DINAMICA_G58_STRINGPROBLEM_HPP

#include "estrutura/alinhamento/IAlignmentProblem.hpp"

#include <string>

class StringProblem : public estrutura::alinhamento::IAlignmentProblem {
    std::string x;
    std::string y;
    int mismatchCost;
    int unmatchedCost;

public:
    StringProblem(std::string x, std::string y, int mismatchCost = 1, int unmatchedCost = 1)
        : x(x), y(y), mismatchCost(mismatchCost), unmatchedCost(unmatchedCost) {
    }

    [[nodiscard]] int lengthX() const override { return static_cast<int>(x.size()); }
    [[nodiscard]] int lengthY() const override { return static_cast<int>(y.size()); }

    [[nodiscard]] int pairCost(const int xIndex, const int yIndex) const override {
        return x.at(xIndex) == y.at(yIndex) ? 0 : mismatchCost;
    }

    [[nodiscard]] int unmatchedXCost([[maybe_unused]] int xIndex) const override { return unmatchedCost; }
    [[nodiscard]] int unmatchedYCost([[maybe_unused]] int yIndex) const override { return unmatchedCost; }
};

#endif //PROGRAMACAO_DINAMICA_G58_STRINGPROBLEM_HPP
