#include "DiffAssembler.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::nucleo {

DiffAssembler::DiffAssembler(const alinhamento::IAligner& aligner)
	: aligner(aligner) {
}

TextDiff DiffAssembler::assemble(const std::vector<std::string>& beforeLines, const std::vector<std::string>& afterLines, const alinhamento::Alignment& lineAlignment) const {
	notImplemented("DiffAssembler::assemble", beforeLines, afterLines, lineAlignment);
}

std::vector<WordEdit> DiffAssembler::wordEdits(const std::string& beforeLine, const std::string& afterLine) const {
	notImplemented("DiffAssembler::wordEdits", beforeLine, afterLine, aligner);
}

}  // namespace estrutura::nucleo
