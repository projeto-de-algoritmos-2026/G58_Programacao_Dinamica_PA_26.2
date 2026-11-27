#ifndef PROGRAMACAO_DINAMICA_G58_ALIGNMENTORACLE_HPP
#define PROGRAMACAO_DINAMICA_G58_ALIGNMENTORACLE_HPP

#include <algorithm>
#include <limits>
#include <vector>

#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/alinhamento/IAlignmentProblem.hpp"

namespace oraculo {
    using estrutura::alinhamento::AlignmentColumn;
    using estrutura::alinhamento::IAlignmentProblem;

    inline bool isValid(const IAlignmentProblem &problem, const std::vector<AlignmentColumn> &columns) {
        int nextXIndex = 0;
        int nextYIndex = 0;

        for (const AlignmentColumn &column: columns) {
            if (!column.xIndex.has_value() && !column.yIndex.has_value()) {
                return false;
            }
            if (column.xIndex.has_value()) {
                if (*column.xIndex != nextXIndex) {
                    return false;
                }
                ++nextXIndex;
            }
            if (column.yIndex.has_value()) {
                if (*column.yIndex != nextYIndex) {
                    return false;
                }
                ++nextYIndex;
            }
        }

        return nextXIndex == problem.lengthX() && nextYIndex == problem.lengthY();
    }

    inline int recomputedCost(const IAlignmentProblem &problem, const std::vector<AlignmentColumn> &columns) {
        int cost = 0;

        for (const AlignmentColumn &column: columns) {
            if (column.xIndex.has_value() && column.yIndex.has_value()) {
                cost += problem.pairCost(*column.xIndex, *column.yIndex);
            } else if (column.xIndex.has_value()) {
                cost += problem.unmatchedXCost(*column.xIndex);
            } else if (column.yIndex.has_value()) {
                cost += problem.unmatchedYCost(*column.yIndex);
            }
        }

        return cost;
    }

    inline int bruteForceCost(const IAlignmentProblem &problem, const int xPrefixLength, const int yPrefixLength) {
        if (xPrefixLength == 0 && yPrefixLength == 0) {
            return 0;
        }

        int best = std::numeric_limits<int>::max();

        if (xPrefixLength > 0 && yPrefixLength > 0) {
            best = std::min(best, problem.pairCost(xPrefixLength - 1, yPrefixLength - 1)
                                  + bruteForceCost(problem, xPrefixLength - 1, yPrefixLength - 1));
        }
        if (xPrefixLength > 0) {
            best = std::min(best, problem.unmatchedXCost(xPrefixLength - 1)
                                  + bruteForceCost(problem, xPrefixLength - 1, yPrefixLength));
        }
        if (yPrefixLength > 0) {
            best = std::min(best, problem.unmatchedYCost(yPrefixLength - 1)
                                  + bruteForceCost(problem, xPrefixLength, yPrefixLength - 1));
        }

        return best;
    }

    inline int bruteForceCost(const IAlignmentProblem &problem) {
        return bruteForceCost(problem, problem.lengthX(), problem.lengthY());
    }
} // namespace oraculo

#endif //PROGRAMACAO_DINAMICA_G58_ALIGNMENTORACLE_HPP