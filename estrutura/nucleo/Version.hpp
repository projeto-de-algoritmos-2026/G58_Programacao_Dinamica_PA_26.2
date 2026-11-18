#ifndef ESTRUTURA_NUCLEO_VERSION_H
#define ESTRUTURA_NUCLEO_VERSION_H

#include <string>

namespace estrutura::nucleo {
struct Version {

	int number = 0;

	std::string message;

	std::string createdAt;

	std::string text;

};

}  // namespace estrutura::nucleo
#endif
