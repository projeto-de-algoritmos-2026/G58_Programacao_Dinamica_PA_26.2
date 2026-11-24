#include "DiffAssembler.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::nucleo {

DiffAssembler::DiffAssembler(const alinhamento::IAligner& aligner)
	: aligner(aligner) {
}

TextDiff DiffAssembler::assemble(const std::vector<std::string>& beforeLines, const std::vector<std::string>& afterLines, const alinhamento::Alignment& lineAlignment) const {
	TextDiff result;
	for (const alinhamento::AlignmentColumn& column : lineAlignment.columns) {
		LineEdit line;
		line.kind = EditKind::Kept;
		line.beforeIndex = column.xIndex;
		line.afterIndex = column.yIndex;

		line.beforeText = beforeLines.at(*column.xIndex);
		line.afterText = afterLines.at(*column.yIndex);

		result.lines.push_back(line);
	}
	return result;
}

std::vector<WordEdit> DiffAssembler::wordEdits(const std::string& beforeLine, const std::string& afterLine) const {
	notImplemented("DiffAssembler::wordEdits", beforeLine, afterLine, aligner);
}

}  // namespace estrutura::nucleo
