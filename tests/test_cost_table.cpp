#include <gtest/gtest.h>

#include "estrutura/alinhamento/CostTable.hpp"

using estrutura::alinhamento::CostTable;

TEST(CostTable, CadaCelulaGuardaOProprioValor) {
    CostTable table(2, 3);

    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 3; ++j) {
            table.at(i, j) = 10 * i + j;
        }
    }

    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 3; ++j) {
            EXPECT_EQ(table.at(i, j), 10 * i + j);
        }
    }
}

TEST(CostTable, AtConstLeOQueFoiGravado) {
    CostTable table(1, 1);
    table.at(1, 1) = 7;

    const CostTable &readOnly = table;

    EXPECT_EQ(readOnly.at(1, 1), 7);
}