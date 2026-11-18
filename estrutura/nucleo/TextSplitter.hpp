#ifndef ESTRUTURA_NUCLEO_TEXT_SPLITTER_H
#define ESTRUTURA_NUCLEO_TEXT_SPLITTER_H

#include <string>
#include <vector>

namespace estrutura::nucleo {
class TextSplitter {
public:
	[[nodiscard]] static std::vector<std::string> lines(const std::string& text);

	[[nodiscard]] static std::vector<std::string> words(const std::string& line);

};

}  // namespace estrutura::nucleo
#endif
