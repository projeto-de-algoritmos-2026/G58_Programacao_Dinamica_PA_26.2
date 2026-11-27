#ifndef ESTRUTURA_NUCLEO_WORD_EDIT_H
#define ESTRUTURA_NUCLEO_WORD_EDIT_H

#include <string>

#include "estrutura/nucleo/EditKind.hpp"

namespace estrutura::nucleo {
    struct WordEdit {
        EditKind kind = EditKind::Kept;

        std::string before;

        std::string after;
    };
} // namespace estrutura::nucleo
#endif