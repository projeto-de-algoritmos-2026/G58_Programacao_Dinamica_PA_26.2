#ifndef ESTRUTURA_NOT_IMPLEMENTED_H
#define ESTRUTURA_NOT_IMPLEMENTED_H

#include <stdexcept>
#include <string>

namespace estrutura {

// Corpo provisório dos métodos do esqueleto: o teste fica vermelho com o nome do método.
// Os argumentos só existem para o compilador não avisar de parâmetro sem uso.
// Quando o último método for implementado, este arquivo pode ser apagado.
template <typename... Unused>
[[noreturn]] void notImplemented(const char* method, const Unused&...) {
	throw std::logic_error(std::string(method) + ": não implementado");
}

}  // namespace estrutura
#endif
