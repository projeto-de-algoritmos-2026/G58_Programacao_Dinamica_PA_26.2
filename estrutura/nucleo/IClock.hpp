#ifndef ESTRUTURA_NUCLEO_I_CLOCK_H
#define ESTRUTURA_NUCLEO_I_CLOCK_H

#include <string>

namespace estrutura::nucleo {
    class IClock {
    public:
        virtual ~IClock() = default;

        [[nodiscard]] virtual std::string now() const = 0;
    };
} // namespace estrutura::nucleo
#endif