#include "TerminalUI.hpp"

#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <optional>

#include "estrutura/NotImplemented.hpp"

namespace estrutura::terminal {

	namespace {
		std::optional<std::string> readFile(const std::filesystem::path& path) {
			std::ifstream file(path);
			if (!file) { return std::nullopt; }
			std::ostringstream content;
			content << file.rdbuf();
			return content.str();
		}
	}

TerminalUI::TerminalUI(const nucleo::IDiffer& differ, std::istream& input, std::ostream& output)
	: differ(differ), input(input), output(output) {
}

void TerminalUI::run() const {

	std::string line;

	while(std::getline(input, line)) {

		std::istringstream lineStream(line);

		std::string command;
		lineStream >> command;

		if (command == "sair") { break; }

		if (command == "comparar") {
			std::filesystem::path firstPath;
			std::filesystem::path secondPath;

			lineStream >> firstPath >> secondPath;

			const std::optional<std::string> before = readFile(firstPath);
			const std::optional<std::string> after = readFile(secondPath);

			if (!before.has_value()) {
				output << "Não foi possível abrir o arquivo: " << firstPath << "\n";
			} else if (!after.has_value()) {
				output << "Não foi possível abrir o arquivo: " << secondPath << "\n";
			} else {
				const nucleo::TextDiff diff = differ.diff(*before, *after);
			}

		} else if (command == "") {
			// linha vazia não faz nada
		} else if (command == "ajuda") {
			output  << "comparar <a> <b>	compara os arquivos a e b\n"
			<< "ajuda						esta lista\n"
			<< "sair						encerra\n";
		} else {
			output << "Comando desconhecido.\n";
		}

	}

}

void TerminalUI::printDiff(const nucleo::TextDiff& diff) {
	notImplemented("TerminalUI::printDiff", diff);
}

void TerminalUI::printVersions(const std::vector<nucleo::Version>& versions) {
	notImplemented("TerminalUI::printVersions", versions);
}

}  // namespace estrutura::terminal
