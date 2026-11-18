#include "TerminalUI.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::terminal {

TerminalUI::TerminalUI(const nucleo::IDiffer& differ)
	: differ(differ) {
}

void TerminalUI::run() const {
	notImplemented("TerminalUI::run", differ);
}

void TerminalUI::printDiff(const nucleo::TextDiff& diff) {
	notImplemented("TerminalUI::printDiff", diff);
}

void TerminalUI::printVersions(const std::vector<nucleo::Version>& versions) {
	notImplemented("TerminalUI::printVersions", versions);
}

}  // namespace estrutura::terminal
