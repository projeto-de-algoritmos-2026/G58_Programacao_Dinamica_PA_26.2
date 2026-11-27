#ifndef PROGRAMACAO_DINAMICA_G58_RANDOMPROBLEM_HPP
#define PROGRAMACAO_DINAMICA_G58_RANDOMPROBLEM_HPP

#include <random>
#include <string>
#include <utility>
#include <vector>

#include "estrutura/alinhamento/IAlignmentProblem.hpp"

class ExplicitCostProblem : public estrutura::alinhamento::IAlignmentProblem {
    std::vector<std::vector<int> > pairCosts;
    std::vector<int> unmatchedXCosts;
    std::vector<int> unmatchedYCosts;

public:
    ExplicitCostProblem(std::vector<std::vector<int> > pairCosts, std::vector<int> unmatchedXCosts,
                        std::vector<int> unmatchedYCosts)
        : pairCosts(std::move(pairCosts)), unmatchedXCosts(std::move(unmatchedXCosts)),
          unmatchedYCosts(std::move(unmatchedYCosts)) {
    }

    [[nodiscard]] int lengthX() const override { return static_cast<int>(unmatchedXCosts.size()); }
    [[nodiscard]] int lengthY() const override { return static_cast<int>(unmatchedYCosts.size()); }

    [[nodiscard]] int pairCost(const int xIndex, const int yIndex) const override {
        return pairCosts.at(xIndex).at(yIndex);
    }

    [[nodiscard]] int unmatchedXCost(const int xIndex) const override { return unmatchedXCosts.at(xIndex); }
    [[nodiscard]] int unmatchedYCost(const int yIndex) const override { return unmatchedYCosts.at(yIndex); }
};

class RandomProblemGenerator {
    std::mt19937 engine;

public:
    explicit RandomProblemGenerator(const unsigned seed) : engine(seed) {
    }

    int between(const int minimum, const int maximum) {
        return minimum + static_cast<int>(engine() % static_cast<unsigned>(maximum - minimum + 1));
    }

    std::string text(const int maxLength, const std::string &alphabet) {
        std::string result;
        const int length = between(0, maxLength);
        for (int position = 0; position < length; ++position) {
            result += alphabet.at(between(0, static_cast<int>(alphabet.size()) - 1));
        }
        return result;
    }

    ExplicitCostProblem explicitCostProblem(const int maxLength, const int maxCost) {
        const int lengthX = between(0, maxLength);
        const int lengthY = between(0, maxLength);

        std::vector<std::vector<int> > pairCosts(lengthX, std::vector<int>(lengthY));
        for (std::vector<int> &row: pairCosts) {
            for (int &cost: row) {
                cost = between(0, maxCost);
            }
        }

        std::vector<int> unmatchedXCosts(lengthX);
        for (int &cost: unmatchedXCosts) {
            cost = between(0, maxCost);
        }

        std::vector<int> unmatchedYCosts(lengthY);
        for (int &cost: unmatchedYCosts) {
            cost = between(0, maxCost);
        }

        return {std::move(pairCosts), std::move(unmatchedXCosts), std::move(unmatchedYCosts)};
    }

    std::vector<std::string> lines(const int maxCount, const std::vector<std::string> &vocabulary) {
        std::vector<std::string> result;
        const int count = between(0, maxCount);
        for (int position = 0; position < count; ++position) {
            result.push_back(vocabulary.at(between(0, static_cast<int>(vocabulary.size()) - 1)));
        }
        return result;
    }
};

#endif //PROGRAMACAO_DINAMICA_G58_RANDOMPROBLEM_HPP