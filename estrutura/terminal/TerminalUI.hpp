#ifndef ESTRUTURA_TERMINAL_TERMINAL_U_I_H
#define ESTRUTURA_TERMINAL_TERMINAL_U_I_H

#include <vector>

#include "estrutura/nucleo/IDiffer.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/Version.hpp"

namespace estrutura::terminal {
class TerminalUI {

	const nucleo::IDiffer& differ;

	static void printDiff(const nucleo::TextDiff& diff);

	static void printVersions(const std::vector<nucleo::Version>& versions);

public:
	explicit TerminalUI(const nucleo::IDiffer& differ);

	void run() const;

};

}  // namespace estrutura::terminal
#endif
