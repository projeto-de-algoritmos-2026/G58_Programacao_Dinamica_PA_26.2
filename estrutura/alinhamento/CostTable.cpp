#include "CostTable.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::alinhamento {

CostTable::CostTable(const int lengthX, const int lengthY) {
	notImplemented("CostTable::CostTable", lengthX, lengthY, rowLength, cells);
}

int& CostTable::at(const int xPrefixLength, const int yPrefixLength) {
	notImplemented("CostTable::at", xPrefixLength, yPrefixLength);
}

int CostTable::at(const int xPrefixLength, const int yPrefixLength) const {
	notImplemented("CostTable::at const", xPrefixLength, yPrefixLength);
}

}  // namespace estrutura::alinhamento
