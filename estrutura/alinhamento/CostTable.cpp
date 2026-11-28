#include "CostTable.hpp"

#include <cstddef>

namespace estrutura::alinhamento {
    namespace {
        std::size_t cellIndex(const int xPrefixLength, const int yPrefixLength, const int rowLength) {
            return static_cast<std::size_t>(xPrefixLength) * static_cast<std::size_t>(rowLength) + static_cast<std::size_t>(yPrefixLength);
        }
    }

    CostTable::CostTable(const int lengthX, const int lengthY)
        : rowLength(lengthY + 1),
          cells((lengthX + 1) * (lengthY + 1)) {
    }

    int &CostTable::at(const int xPrefixLength, const int yPrefixLength) {
        return cells[cellIndex(xPrefixLength, yPrefixLength, rowLength)];
    }

    int CostTable::at(const int xPrefixLength, const int yPrefixLength) const {
        return cells[cellIndex(xPrefixLength, yPrefixLength, rowLength)];
    }
} // namespace estrutura::alinhamento