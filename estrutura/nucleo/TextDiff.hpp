#ifndef ESTRUTURA_NUCLEO_TEXT_DIFF_H
#define ESTRUTURA_NUCLEO_TEXT_DIFF_H

#include <vector>

#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/LineEdit.hpp"

namespace estrutura::nucleo {
struct TextDiff {

	std::vector<LineEdit> lines;

	[[nodiscard]] int count(EditKind kind) const;

	[[nodiscard]] bool isIdentical() const;

};

}  // namespace estrutura::nucleo
#endif
