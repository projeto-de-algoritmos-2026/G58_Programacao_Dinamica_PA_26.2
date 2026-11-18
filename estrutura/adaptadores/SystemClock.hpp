#ifndef ESTRUTURA_ADAPTADORES_SYSTEM_CLOCK_H
#define ESTRUTURA_ADAPTADORES_SYSTEM_CLOCK_H

#include <string>

#include "estrutura/nucleo/IClock.hpp"

namespace estrutura::adaptadores {
class SystemClock : public nucleo::IClock {
public:
	[[nodiscard]] std::string now() const override;

};

}  // namespace estrutura::adaptadores
#endif
