#ifndef ESTRUTURA_ALINHAMENTO_LONGEST_INCREASING_SUBSEQUENCE_H
#define ESTRUTURA_ALINHAMENTO_LONGEST_INCREASING_SUBSEQUENCE_H

#include <vector>

namespace estrutura::alinhamento {
    class LongestIncreasingSubsequence {
    public:
        [[nodiscard]] static std::vector<int> of(const std::vector<int> &values);

        [[nodiscard]] static int lengthQuadratic(const std::vector<int> &values);
    };
} // namespace estrutura::alinhamento
#endif