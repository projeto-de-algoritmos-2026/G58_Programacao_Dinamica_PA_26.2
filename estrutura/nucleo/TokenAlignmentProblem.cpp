#include "TokenAlignmentProblem.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::nucleo {

TokenAlignmentProblem::TokenAlignmentProblem(const std::vector<std::string>& before, const std::vector<std::string>& after, const int mismatchCost, const int unmatchedCost)
	: before(before), after(after), mismatchCost(mismatchCost), unmatchedCost(unmatchedCost) {
}

TokenAlignmentProblem TokenAlignmentProblem::forLines(const std::vector<std::string>& before, const std::vector<std::string>& after) {
	notImplemented("TokenAlignmentProblem::forLines", before, after);
}

TokenAlignmentProblem TokenAlignmentProblem::forWords(const std::vector<std::string>& before, const std::vector<std::string>& after) {
	notImplemented("TokenAlignmentProblem::forWords", before, after);
}

int TokenAlignmentProblem::lengthX() const { return static_cast<int>(before.size()); }

int TokenAlignmentProblem::lengthY() const { return static_cast<int>(after.size()); }

int TokenAlignmentProblem::pairCost(const int xIndex, const int yIndex) const {
	notImplemented("TokenAlignmentProblem::pairCost", xIndex, yIndex, mismatchCost);
}

int TokenAlignmentProblem::unmatchedXCost(const int xIndex) const {
	notImplemented("TokenAlignmentProblem::unmatchedXCost", xIndex, unmatchedCost);
}

int TokenAlignmentProblem::unmatchedYCost(const int yIndex) const {
	notImplemented("TokenAlignmentProblem::unmatchedYCost", yIndex, unmatchedCost);
}

}  // namespace estrutura::nucleo
