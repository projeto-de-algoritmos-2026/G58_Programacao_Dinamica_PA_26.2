#include "TextDiff.hpp"

#include "estrutura/NotImplemented.hpp"

#include <algorithm>

namespace estrutura::nucleo {

int TextDiff::count(const EditKind kind) const {

	return static_cast<int> (std::count_if(lines.begin(), lines.end(), [&kind](const LineEdit& line) {
		return line.kind == kind;
	}));

}

bool TextDiff::isIdentical() const {
	notImplemented("TextDiff::isIdentical");
}

}  // namespace estrutura::nucleo
