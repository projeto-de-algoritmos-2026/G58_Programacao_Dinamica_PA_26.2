#ifndef ESTRUTURA_NUCLEO_DIFF_ASSEMBLER_H
#define ESTRUTURA_NUCLEO_DIFF_ASSEMBLER_H

#include <string>
#include <vector>

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/IAligner.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/WordEdit.hpp"

namespace estrutura::nucleo {
class DiffAssembler {

	const alinhamento::IAligner& aligner;

	[[nodiscard]] std::vector<WordEdit> wordEdits(const std::string& beforeLine, const std::string& afterLine) const;

public:
	explicit DiffAssembler(const alinhamento::IAligner& aligner);

	[[nodiscard]] TextDiff assemble(const std::vector<std::string>& beforeLines, const std::vector<std::string>& afterLines, const alinhamento::Alignment& lineAlignment) const;

};

}  // namespace estrutura::nucleo
#endif
