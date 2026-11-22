#include "NeedlemanWunschAligner.hpp"

#include <algorithm>

namespace estrutura::alinhamento {
	namespace {
		int costIfPaired(const IAlignmentProblem &problem, const CostTable &costTable, const int xPrefixLength,
		                 const int yPrefixLength) {
			return costTable.at(xPrefixLength - 1, yPrefixLength - 1) + problem.pairCost(
				       xPrefixLength - 1, yPrefixLength - 1);
		}

		int costIfXUnmatched(const IAlignmentProblem &problem, const CostTable &costTable, const int xPrefixLength,
		                     const int yPrefixLength) {
			return costTable.at(xPrefixLength - 1, yPrefixLength) + problem.unmatchedXCost(xPrefixLength - 1);
		}

		int costIfYUnmatched(const IAlignmentProblem &problem, const CostTable &costTable, const int xPrefixLength,
		                     const int yPrefixLength) {
			return costTable.at(xPrefixLength, yPrefixLength - 1) + problem.unmatchedYCost(yPrefixLength - 1);
		}

		bool cameFromPair(const IAlignmentProblem& problem, const CostTable& costTable, const int xPrefixLength, const int yPrefixLength) {
			return xPrefixLength > 0 && yPrefixLength > 0 && costTable.at(xPrefixLength, yPrefixLength) == costIfPaired(
					   problem, costTable, xPrefixLength, yPrefixLength);
		}

		bool cameFromXUnmatched(const IAlignmentProblem& problem, const CostTable& costTable, const int xPrefixLength, const int yPrefixLength) {
			return xPrefixLength > 0 && costTable.at(xPrefixLength, yPrefixLength) == costIfXUnmatched(
					   problem, costTable, xPrefixLength, yPrefixLength);
		}
	}

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
		costTable.at(xPrefixLength, 0) = costIfXUnmatched(problem, costTable, xPrefixLength, 0);
	}

	for (int yPrefixLength = 1; yPrefixLength <= lengthY; yPrefixLength++) {
		costTable.at(0, yPrefixLength) = costIfYUnmatched(problem, costTable, 0, yPrefixLength);
	}

	for (int xPrefixLength = 1; xPrefixLength <= lengthX; xPrefixLength++) {
		for (int yPrefixLength = 1; yPrefixLength <= lengthY; yPrefixLength++) {
			costTable.at(xPrefixLength, yPrefixLength) = std::min({
				costIfPaired(problem, costTable, xPrefixLength, yPrefixLength),
				costIfXUnmatched(problem, costTable, xPrefixLength, yPrefixLength),
				costIfYUnmatched(problem, costTable, xPrefixLength, yPrefixLength)
			});
		}
	}

	return costTable;
}

std::vector<AlignmentColumn> NeedlemanWunschAligner::traceback(const IAlignmentProblem& problem, const CostTable& costTable) {

	int xPrefixLength = problem.lengthX();
	int yPrefixLength = problem.lengthY();

	std::vector<AlignmentColumn> columns;

	while (xPrefixLength > 0 || yPrefixLength > 0) {
		if (cameFromPair(problem, costTable, xPrefixLength, yPrefixLength)) {
			columns.push_back({xPrefixLength - 1, yPrefixLength - 1});
			xPrefixLength--;
			yPrefixLength--;
		} else if (cameFromXUnmatched(problem, costTable, xPrefixLength, yPrefixLength)) {
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
