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
		line.beforeIndex = column.xIndex;
		line.afterIndex = column.yIndex;

		if (column.xIndex.has_value() && column.yIndex.has_value()) {
			line.kind = EditKind::Kept;
			line.beforeText = beforeLines.at(*column.xIndex);
			line.afterText = afterLines.at(*column.yIndex);
		} else if (column.xIndex.has_value()) {
			line.kind = EditKind::Removed;
			line.beforeText = beforeLines.at(*column.xIndex);
		} else {
			line.kind = EditKind::Added;
			line.afterText = afterLines.at(*column.yIndex);
		}

		result.lines.push_back(line);
	}
	return result;
}

std::vector<WordEdit> DiffAssembler::wordEdits(const std::string& beforeLine, const std::string& afterLine) const {
	notImplemented("DiffAssembler::wordEdits", beforeLine, afterLine, aligner);
}

}  // namespace estrutura::nucleo
