#include "TerminalUI.hpp"

#include <iostream>
#include <string>

#include "estrutura/NotImplemented.hpp"

namespace estrutura::terminal {

TerminalUI::TerminalUI(const nucleo::IDiffer& differ, std::istream& input, std::ostream& output)
	: differ(differ), input(input), output(output) {
}

void TerminalUI::run() const {

	std::string line;

	while(std::getline(input, line)) {

		if (line == "sair") break;

		if (line == "ajuda") {
			output  << "comparar <a> <b>	compara os arquivos a e b\n"
			<< "ajuda						esta lista\n"
			<< "sair						encerra\n";
		}

		output << "Comando desconhecido.";

	}

}

void TerminalUI::printDiff(const nucleo::TextDiff& diff) {
	notImplemented("TerminalUI::printDiff", diff);
}

void TerminalUI::printVersions(const std::vector<nucleo::Version>& versions) {
	notImplemented("TerminalUI::printVersions", versions);
}

}  // namespace estrutura::terminal
