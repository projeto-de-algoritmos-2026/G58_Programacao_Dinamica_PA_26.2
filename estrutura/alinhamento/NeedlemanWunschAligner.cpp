#include "NeedlemanWunschAligner.hpp"

#include <algorithm>

namespace estrutura::alinhamento {

Alignment NeedlemanWunschAligner::align(const IAlignmentProblem& problem) const {

	const CostTable costTable = fillTable(problem);

	Alignment alignment;
	alignment.cost = costTable.at(problem.lengthX(), problem.lengthY());

	alignment.columns = traceback(problem, costTable);

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

	int xPrefixLength = problem.lengthX();
	int yPrefixLength = problem.lengthY();

	std::vector<AlignmentColumn> columns;

	while (xPrefixLength > 0 || yPrefixLength > 0) {
		if (xPrefixLength > 0 && yPrefixLength > 0 && costTable.at(xPrefixLength, yPrefixLength) == costTable.at(xPrefixLength - 1, yPrefixLength - 1) + problem.pairCost(xPrefixLength - 1, yPrefixLength - 1)) {
			columns.push_back({xPrefixLength - 1, yPrefixLength - 1});
			xPrefixLength--;
			yPrefixLength--;
		} else if (xPrefixLength > 0 && costTable.at(xPrefixLength, yPrefixLength) == costTable.at(xPrefixLength - 1, yPrefixLength) + problem.unmatchedXCost(xPrefixLength - 1)) {
			columns.push_back({xPrefixLength - 1, std::nullopt});
			xPrefixLength--;
		} else {
			columns.push_back({std::nullopt, yPrefixLength - 1});
			yPrefixLength--;
		}
	}

	std::reverse(columns.begin(), columns.end());

	return columns;

}

}  // namespace estrutura::alinhamento
