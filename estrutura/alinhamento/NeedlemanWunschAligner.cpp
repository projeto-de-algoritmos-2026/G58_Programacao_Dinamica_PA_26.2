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

	const int m = problem.lengthX();
	const int n = problem.lengthY();

	CostTable costTable(m, n);

	for (int i = 1; i <= m; i++) {
		costTable.at(i, 0) = costTable.at(i -1, 0) + problem.unmatchedXCost(i -1);
	}

	for (int j = 1; j <= n; j++) {
		costTable.at(0, j) = costTable.at(0, j -1) + problem.unmatchedYCost(j -1);
	}

	return costTable;
}

std::vector<AlignmentColumn> NeedlemanWunschAligner::traceback(const IAlignmentProblem& problem, const CostTable& costTable) {
	notImplemented("NeedlemanWunschAligner::traceback", problem, costTable);
}

}  // namespace estrutura::alinhamento
