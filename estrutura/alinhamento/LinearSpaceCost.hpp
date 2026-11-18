#ifndef ESTRUTURA_ALINHAMENTO_LINEAR_SPACE_COST_H
#define ESTRUTURA_ALINHAMENTO_LINEAR_SPACE_COST_H

#include <vector>

#include "estrutura/alinhamento/IAlignmentProblem.hpp"

namespace estrutura::alinhamento {
class LinearSpaceCost {
public:
	[[nodiscard]] static std::vector<int> forward(const IAlignmentProblem& problem);

	[[nodiscard]] static std::vector<int> backward(const IAlignmentProblem& problem);

	[[nodiscard]] static int optimalCost(const IAlignmentProblem& problem);

};

}  // namespace estrutura::alinhamento
#endif
