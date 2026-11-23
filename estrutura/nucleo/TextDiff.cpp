#include "TextDiff.hpp"

#include <algorithm>

namespace estrutura::nucleo {

int TextDiff::count(const EditKind kind) const {

	return static_cast<int> (std::count_if(lines.begin(), lines.end(), [&kind](const LineEdit& line) {
		return line.kind == kind;
	}));

}

bool TextDiff::isIdentical() const {

	return std::all_of(lines.begin(), lines.end(), [] (const LineEdit& line) {
		return line.kind == EditKind::Kept;
	});

}

}  // namespace estrutura::nucleo
