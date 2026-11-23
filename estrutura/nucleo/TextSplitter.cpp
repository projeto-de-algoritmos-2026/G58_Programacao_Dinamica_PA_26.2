#include "TextSplitter.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::nucleo {

std::vector<std::string> TextSplitter::lines(const std::string& text) {
	return {};
}

std::vector<std::string> TextSplitter::words(const std::string& line) {
	notImplemented("TextSplitter::words", line);
}

}  // namespace estrutura::nucleo
