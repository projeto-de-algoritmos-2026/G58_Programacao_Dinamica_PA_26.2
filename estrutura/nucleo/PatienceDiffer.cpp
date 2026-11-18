#include "PatienceDiffer.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::nucleo {

PatienceDiffer::PatienceDiffer(const alinhamento::IAligner& aligner)
	: aligner(aligner) {
}

TextDiff PatienceDiffer::diff(const std::string& before, const std::string& after) const {
	notImplemented("PatienceDiffer::diff", before, after, aligner);
}

std::vector<alinhamento::AlignmentColumn> PatienceDiffer::anchors(const std::vector<std::string>& before, const std::vector<std::string>& after) {
	notImplemented("PatienceDiffer::anchors", before, after);
}

}  // namespace estrutura::nucleo
