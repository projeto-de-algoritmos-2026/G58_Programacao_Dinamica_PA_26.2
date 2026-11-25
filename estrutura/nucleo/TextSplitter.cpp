#include "TextSplitter.hpp"

#include <sstream>
#include <string>

namespace estrutura::nucleo {

std::vector<std::string> TextSplitter::lines(const std::string& text) {

	std::istringstream textStream(text);

	std::string line;

	std::vector<std::string> result;

	while (std::getline(textStream, line)) {
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		result.push_back(line);
	}

	return result;
}

std::vector<std::string> TextSplitter::words(const std::string& line) {

	std::istringstream textStream(line);

	std::string word;

	std::vector<std::string> result;

	while (textStream >> word) {
		result.push_back(word);
	}

	return result;
}

}  // namespace estrutura::nucleo
