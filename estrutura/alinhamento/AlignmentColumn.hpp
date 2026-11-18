#ifndef ESTRUTURA_ALINHAMENTO_ALIGNMENT_COLUMN_H
#define ESTRUTURA_ALINHAMENTO_ALIGNMENT_COLUMN_H

#include <optional>

namespace estrutura::alinhamento {
struct AlignmentColumn {

	std::optional<int> xIndex;

	std::optional<int> yIndex;

	[[nodiscard]] bool operator==(const AlignmentColumn& other) const;

};

}  // namespace estrutura::alinhamento
#endif
