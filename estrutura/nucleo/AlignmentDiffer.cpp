#include "AlignmentDiffer.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::nucleo {

AlignmentDiffer::AlignmentDiffer(const alinhamento::IAligner& aligner)
	: aligner(aligner) {
}

TextDiff AlignmentDiffer::diff(const std::string& before, const std::string& after) const {
	notImplemented("AlignmentDiffer::diff", before, after, aligner);
}

}  // namespace estrutura::nucleo
