#ifndef ESTRUTURA_ALINHAMENTO_ALIGNMENT_H
#define ESTRUTURA_ALINHAMENTO_ALIGNMENT_H

#include <vector>

#include "estrutura/alinhamento/AlignmentColumn.hpp"

namespace estrutura::alinhamento {
    struct Alignment {
        int cost = 0;

        std::vector<AlignmentColumn> columns;
    };
} // namespace estrutura::alinhamento
#endif