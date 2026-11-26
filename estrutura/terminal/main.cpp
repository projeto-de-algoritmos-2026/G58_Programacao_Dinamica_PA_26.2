#include <exception>
#include <iostream>

#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/AlignmentDiffer.hpp"
#include "estrutura/terminal/TerminalUI.hpp"

using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::AlignmentDiffer;
using estrutura::terminal::TerminalUI;

int main() {
	try {
		NeedlemanWunschAligner aligner;
		AlignmentDiffer differ(aligner);
		TerminalUI terminal(differ, std::cin, std::cout);
		terminal.run();

	} catch (const std::exception& e) {
		std::cerr << "Erro: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
