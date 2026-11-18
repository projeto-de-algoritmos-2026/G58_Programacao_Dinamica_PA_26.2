#ifndef ESTRUTURA_NUCLEO_ALIGNMENT_DIFFER_H
#define ESTRUTURA_NUCLEO_ALIGNMENT_DIFFER_H

#include <string>

#include "estrutura/alinhamento/IAligner.hpp"
#include "estrutura/nucleo/IDiffer.hpp"
#include "estrutura/nucleo/TextDiff.hpp"

namespace estrutura::nucleo {
class AlignmentDiffer : public IDiffer {

	const alinhamento::IAligner& aligner;

public:
	explicit AlignmentDiffer(const alinhamento::IAligner& aligner);

	[[nodiscard]] TextDiff diff(const std::string& before, const std::string& after) const override;

};

}  // namespace estrutura::nucleo
#endif
