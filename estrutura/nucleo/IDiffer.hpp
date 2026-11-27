#ifndef ESTRUTURA_NUCLEO_I_DIFFER_H
#define ESTRUTURA_NUCLEO_I_DIFFER_H

#include <string>

#include "estrutura/nucleo/TextDiff.hpp"

namespace estrutura::nucleo {
    class IDiffer {
    public:
        virtual ~IDiffer() = default;

        [[nodiscard]] virtual TextDiff diff(const std::string &before, const std::string &after) const = 0;
    };
} // namespace estrutura::nucleo
#endif