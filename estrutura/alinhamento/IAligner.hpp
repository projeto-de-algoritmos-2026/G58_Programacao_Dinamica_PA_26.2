#ifndef ESTRUTURA_ALINHAMENTO_I_ALIGNER_H
#define ESTRUTURA_ALINHAMENTO_I_ALIGNER_H

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/IAlignmentProblem.hpp"

namespace estrutura::alinhamento {
class IAligner {
public:
	virtual ~IAligner() = default;

	[[nodiscard]] virtual Alignment align(const IAlignmentProblem& problem) const = 0;

};

}  // namespace estrutura::alinhamento
#endif
