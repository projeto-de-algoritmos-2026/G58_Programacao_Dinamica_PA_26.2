#ifndef ESTRUTURA_TERMINAL_TERMINAL_U_I_H
#define ESTRUTURA_TERMINAL_TERMINAL_U_I_H

#include <vector>
#include <istream>
#include <ostream>

#include "estrutura/nucleo/IDiffer.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/Version.hpp"

namespace estrutura::terminal {
class TerminalUI {

	const nucleo::IDiffer& differ;
	std::istream& input;
	std::ostream& output;

	void printDiff(const nucleo::TextDiff& diff) const;

	static void printVersions(const std::vector<nucleo::Version>& versions);

public:
	explicit TerminalUI(const nucleo::IDiffer& differ, std::istream& input, std::ostream& output);

	void run() const;

};

}  // namespace estrutura::terminal
#endif
