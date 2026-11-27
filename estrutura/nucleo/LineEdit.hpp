#ifndef ESTRUTURA_NUCLEO_LINE_EDIT_H
#define ESTRUTURA_NUCLEO_LINE_EDIT_H

#include <optional>
#include <string>
#include <vector>

#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/WordEdit.hpp"

namespace estrutura::nucleo {
    struct LineEdit {
        EditKind kind = EditKind::Kept;

        std::optional<int> beforeIndex;

        std::optional<int> afterIndex;

        std::string beforeText;

        std::string afterText;

        std::vector<WordEdit> words;
    };
} // namespace estrutura::nucleo
#endif