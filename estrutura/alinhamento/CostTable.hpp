#ifndef ESTRUTURA_ALINHAMENTO_COST_TABLE_H
#define ESTRUTURA_ALINHAMENTO_COST_TABLE_H

#include <vector>

namespace estrutura::alinhamento {
    class CostTable {
        int rowLength = 0;

        std::vector<int> cells;

    public:
        CostTable(int lengthX, int lengthY);

        [[nodiscard]] int &at(int xPrefixLength, int yPrefixLength);

        [[nodiscard]] int at(int xPrefixLength, int yPrefixLength) const;
    };
} // namespace estrutura::alinhamento
#endif