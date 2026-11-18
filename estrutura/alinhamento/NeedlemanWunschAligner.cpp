#include "NeedlemanWunschAligner.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::alinhamento {

Alignment NeedlemanWunschAligner::align(const IAlignmentProblem& problem) const {
	notImplemented("NeedlemanWunschAligner::align", problem);
}

CostTable NeedlemanWunschAligner::fillTable(const IAlignmentProblem& problem) {
	notImplemented("NeedlemanWunschAligner::fillTable", problem);
}

std::vector<AlignmentColumn> NeedlemanWunschAligner::traceback(const IAlignmentProblem& problem, const CostTable& costTable) {
	notImplemented("NeedlemanWunschAligner::traceback", problem, costTable);
}

}  // namespace estrutura::alinhamento
