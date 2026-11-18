#include "CostTable.hpp"

namespace estrutura::alinhamento {

CostTable::CostTable(const int lengthX, const int lengthY)
	: rowLength(lengthY + 1),
	cells((lengthX + 1) * (lengthY + 1)) {}

int& CostTable::at(const int xPrefixLength, const int yPrefixLength) {
	return cells[xPrefixLength * rowLength + yPrefixLength];
}

int CostTable::at(const int xPrefixLength, const int yPrefixLength) const {
	return cells[xPrefixLength * rowLength + yPrefixLength];
}

}  // namespace estrutura::alinhamento
