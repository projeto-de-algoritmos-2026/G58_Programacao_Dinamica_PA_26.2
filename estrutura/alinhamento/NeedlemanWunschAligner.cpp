#include "NeedlemanWunschAligner.hpp"

#include "estrutura/NotImplemented.hpp"

#include <algorithm>

namespace estrutura::alinhamento {

Alignment NeedlemanWunschAligner::align(const IAlignmentProblem& problem) const {

	const CostTable costTable = fillTable(problem);

	Alignment alignment;
	alignment.cost = costTable.at(problem.lengthX(), problem.lengthY());

	return alignment;
}

CostTable NeedlemanWunschAligner::fillTable(const IAlignmentProblem& problem) {

	const int lengthX = problem.lengthX();
	const int lengthY = problem.lengthY();

	CostTable costTable(lengthX, lengthY);

	for (int xPrefixLength = 1; xPrefixLength <= lengthX; xPrefixLength++) {
		costTable.at(xPrefixLength, 0) = costTable.at(xPrefixLength - 1, 0) + problem.unmatchedXCost(xPrefixLength - 1);
	}

	for (int yPrefixLength = 1; yPrefixLength <= lengthY; yPrefixLength++) {
		costTable.at(0, yPrefixLength) = costTable.at(0, yPrefixLength - 1) + problem.unmatchedYCost(yPrefixLength - 1);
	}

	for (int xPrefixLength = 1; xPrefixLength <= lengthX; xPrefixLength++) {
		for (int yPrefixLength = 1; yPrefixLength <= lengthY; yPrefixLength++) {
			const int pairedCost = costTable.at(xPrefixLength - 1, yPrefixLength - 1) + problem.pairCost(xPrefixLength - 1, yPrefixLength - 1);
			const int xUnmatchedCost = costTable.at(xPrefixLength - 1, yPrefixLength) + problem.unmatchedXCost(xPrefixLength - 1);
			const int yUnmatchedCost = costTable.at(xPrefixLength, yPrefixLength - 1) + problem.unmatchedYCost(yPrefixLength - 1);
			costTable.at(xPrefixLength, yPrefixLength) = std::min({pairedCost, xUnmatchedCost, yUnmatchedCost});
		}
	}

	return costTable;
}

std::vector<AlignmentColumn> NeedlemanWunschAligner::traceback(const IAlignmentProblem& problem, const CostTable& costTable) {
	notImplemented("NeedlemanWunschAligner::traceback", problem, costTable);
}

}  // namespace estrutura::alinhamento
