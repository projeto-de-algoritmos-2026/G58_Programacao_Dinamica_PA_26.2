#ifndef ESTRUTURA_TERMINAL_DIFF_FORMATTER_H
#define ESTRUTURA_TERMINAL_DIFF_FORMATTER_H

#include <string>

#include "estrutura/nucleo/TextDiff.hpp"

namespace estrutura::terminal {
    class DiffFormatter {
    public:
        [[nodiscard]] static std::string format(const nucleo::TextDiff &diff);
    };
}
#endif