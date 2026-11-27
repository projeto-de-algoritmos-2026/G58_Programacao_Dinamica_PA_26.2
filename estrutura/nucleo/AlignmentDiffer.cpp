#include "AlignmentDiffer.hpp"

#include "estrutura/nucleo/DiffAssembler.hpp"
#include "estrutura/nucleo/TextSplitter.hpp"
#include "estrutura/nucleo/TokenAlignmentProblem.hpp"
#include "estrutura/alinhamento/Alignment.hpp"

namespace estrutura::nucleo {
    AlignmentDiffer::AlignmentDiffer(const alinhamento::IAligner &aligner)
        : aligner(aligner) {
    }

    TextDiff AlignmentDiffer::diff(const std::string &before, const std::string &after) const {
        const std::vector<std::string> beforeLines = TextSplitter::lines(before);
        const std::vector<std::string> afterLines = TextSplitter::lines(after);

        const TokenAlignmentProblem lineProblem = TokenAlignmentProblem::forLines(beforeLines, afterLines);

        const alinhamento::Alignment lineAlignment = aligner.align(lineProblem);

        const DiffAssembler assembler(aligner);
        return assembler.assemble(beforeLines, afterLines, lineAlignment);
    }
} // namespace estrutura::nucleo