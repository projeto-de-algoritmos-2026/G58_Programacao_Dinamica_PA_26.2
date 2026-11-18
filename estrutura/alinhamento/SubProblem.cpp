#include "SubProblem.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::alinhamento {

SubProblem::SubProblem(const IAlignmentProblem& whole, const IndexRange xRange, const IndexRange yRange)
	: whole(whole), xRange(xRange), yRange(yRange) {
}

const IAlignmentProblem& SubProblem::wholeProblem() const {
	notImplemented("SubProblem::wholeProblem", whole);
}

IndexRange SubProblem::rangeX() const {
	notImplemented("SubProblem::rangeX", xRange);
}

IndexRange SubProblem::rangeY() const {
	notImplemented("SubProblem::rangeY", yRange);
}

int SubProblem::lengthX() const {
	notImplemented("SubProblem::lengthX");
}

int SubProblem::lengthY() const {
	notImplemented("SubProblem::lengthY");
}

int SubProblem::pairCost(const int xIndex, const int yIndex) const {
	notImplemented("SubProblem::pairCost", xIndex, yIndex);
}

int SubProblem::unmatchedXCost(const int xIndex) const {
	notImplemented("SubProblem::unmatchedXCost", xIndex);
}

int SubProblem::unmatchedYCost(const int yIndex) const {
	notImplemented("SubProblem::unmatchedYCost", yIndex);
}

}  // namespace estrutura::alinhamento
