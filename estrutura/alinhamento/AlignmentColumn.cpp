#include "AlignmentColumn.hpp"

namespace estrutura::alinhamento {
    bool AlignmentColumn::operator==(const AlignmentColumn &other) const {
        return xIndex == other.xIndex && yIndex == other.yIndex;
    }
} // namespace estrutura::alinhamento