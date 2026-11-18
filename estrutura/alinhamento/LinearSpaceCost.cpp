#include "LinearSpaceCost.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::alinhamento {

std::vector<int> LinearSpaceCost::forward(const IAlignmentProblem& problem) {
	notImplemented("LinearSpaceCost::forward", problem);
}

std::vector<int> LinearSpaceCost::backward(const IAlignmentProblem& problem) {
	notImplemented("LinearSpaceCost::backward", problem);
}

int LinearSpaceCost::optimalCost(const IAlignmentProblem& problem) {
	notImplemented("LinearSpaceCost::optimalCost", problem);
}

}  // namespace estrutura::alinhamento
