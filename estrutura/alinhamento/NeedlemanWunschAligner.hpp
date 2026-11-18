#ifndef ESTRUTURA_ALINHAMENTO_NEEDLEMAN_WUNSCH_ALIGNER_H
#define ESTRUTURA_ALINHAMENTO_NEEDLEMAN_WUNSCH_ALIGNER_H

#include <vector>

#include "estrutura/alinhamento/IAligner.hpp"
#include "estrutura/alinhamento/CostTable.hpp"

namespace estrutura::alinhamento {
class NeedlemanWunschAligner : public IAligner {

	[[nodiscard]] static CostTable fillTable(const IAlignmentProblem& problem);

	[[nodiscard]] static std::vector<AlignmentColumn> traceback(const IAlignmentProblem& problem, const CostTable& costTable);

public:
	[[nodiscard]] Alignment align(const IAlignmentProblem& problem) const override;

};

}  // namespace estrutura::alinhamento
#endif
