#include "NeedlemanWunschAligner.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::alinhamento {

Alignment NeedlemanWunschAligner::align(const IAlignmentProblem& problem) const {

	const CostTable costTable = fillTable(problem);

	Alignment alignment;
	alignment.cost = costTable.at(problem.lengthX(), problem.lengthY());

	return alignment;
}

CostTable NeedlemanWunschAligner::fillTable(const IAlignmentProblem& problem) {
	return {problem.lengthX(), problem.lengthY()};
}

std::vector<AlignmentColumn> NeedlemanWunschAligner::traceback(const IAlignmentProblem& problem, const CostTable& costTable) {
	notImplemented("NeedlemanWunschAligner::traceback", problem, costTable);
}

}  // namespace estrutura::alinhamento
