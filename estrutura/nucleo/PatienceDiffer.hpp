#ifndef ESTRUTURA_NUCLEO_PATIENCE_DIFFER_H
#define ESTRUTURA_NUCLEO_PATIENCE_DIFFER_H

#include <string>
#include <vector>

#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/alinhamento/IAligner.hpp"
#include "estrutura/nucleo/IDiffer.hpp"
#include "estrutura/nucleo/TextDiff.hpp"

namespace estrutura::nucleo {
class PatienceDiffer : public IDiffer {

	const alinhamento::IAligner& aligner;

	[[nodiscard]] static std::vector<alinhamento::AlignmentColumn> anchors(const std::vector<std::string>& before, const std::vector<std::string>& after);

public:
	explicit PatienceDiffer(const alinhamento::IAligner& aligner);

	[[nodiscard]] TextDiff diff(const std::string& before, const std::string& after) const override;

};

}  // namespace estrutura::nucleo
#endif
