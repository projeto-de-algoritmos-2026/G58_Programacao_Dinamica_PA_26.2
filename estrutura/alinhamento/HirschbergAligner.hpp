#ifndef ESTRUTURA_ALINHAMENTO_HIRSCHBERG_ALIGNER_H
#define ESTRUTURA_ALINHAMENTO_HIRSCHBERG_ALIGNER_H

#include <vector>

#include "estrutura/alinhamento/IAligner.hpp"
#include "estrutura/alinhamento/SubProblem.hpp"

namespace estrutura::alinhamento {
    class HirschbergAligner : public IAligner {
        void alignRange(const SubProblem &subProblem, std::vector<AlignmentColumn> &columns) const;

        [[nodiscard]] static int splitPoint(const SubProblem &subProblem);

    public:
        [[nodiscard]] Alignment align(const IAlignmentProblem &problem) const override;
    };
} // namespace estrutura::alinhamento
#endif