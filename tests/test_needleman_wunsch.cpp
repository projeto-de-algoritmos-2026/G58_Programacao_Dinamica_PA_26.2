#include <vector>

#include <gtest/gtest.h>

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"

#include "StringProblem.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::AlignmentColumn;
using estrutura::alinhamento::NeedlemanWunschAligner;

TEST(NeedlemanWunschAligner, VazioContraVazioCustaZero) {
    const StringProblem problem("", "");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 0);
    EXPECT_TRUE(result.columns.empty());

}

TEST(NeedlemanWunschAligner, VazioContraABCCusta3) {
    const StringProblem problem("", "abc");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 3);
}

TEST(NeedlemanWunschAligner, ABCContraVazioCusta3) {
    const StringProblem problem("abc", "");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 3);
}

TEST(NeedlemanWunschAligner, ABCContraABDCusta1) {
    const StringProblem problem("abc", "abd");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 1);
}

TEST(NeedlemanWunschAligner, ABCContraABXCCusta1) {
    const StringProblem problem("abc", "abxc");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 1);
}

TEST(NeedlemanWunschAligner, SequenciasIguaisCustamZero) {
    const StringProblem problem("abc", "abc");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 0);
}

TEST(NeedlemanWunschAligner, OcurranceContraOccurrenceCusta2) {
    const StringProblem problem("ocurrance", "occurrence");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 2);
}