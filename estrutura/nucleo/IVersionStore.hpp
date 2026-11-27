#ifndef ESTRUTURA_NUCLEO_I_VERSION_STORE_H
#define ESTRUTURA_NUCLEO_I_VERSION_STORE_H

#include <string>
#include <vector>

#include "estrutura/nucleo/Version.hpp"

namespace estrutura::nucleo {
    class IVersionStore {
    public:
        virtual ~IVersionStore() = default;

        virtual void append(const std::string &document, const Version &version) = 0;

        [[nodiscard]] virtual std::vector<Version> versions(const std::string &document) const = 0;

        [[nodiscard]] virtual std::vector<std::string> documents() const = 0;
    };
} // namespace estrutura::nucleo
#endif