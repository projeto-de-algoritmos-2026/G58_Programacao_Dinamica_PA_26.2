#include "HirschbergAligner.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::alinhamento {
    Alignment HirschbergAligner::align(const IAlignmentProblem &problem) const {
        notImplemented("HirschbergAligner::align", problem);
    }

    void HirschbergAligner::alignRange(const SubProblem &subProblem, std::vector<AlignmentColumn> &columns) const {
        notImplemented("HirschbergAligner::alignRange", subProblem, columns);
    }

    int HirschbergAligner::splitPoint(const SubProblem &subProblem) {
        notImplemented("HirschbergAligner::splitPoint", subProblem);
    }
} // namespace estrutura::alinhamento