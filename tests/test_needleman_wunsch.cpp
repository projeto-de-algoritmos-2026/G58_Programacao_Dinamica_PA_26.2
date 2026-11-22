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

    AlignmentColumn colunaAlinhamentoA;
    colunaAlinhamentoA.yIndex = 0;

    AlignmentColumn colunaAlinhamentoB;
    colunaAlinhamentoB.yIndex = 1;

    AlignmentColumn colunaAlinhamentoC;
    colunaAlinhamentoC.yIndex = 2;

    std::vector<AlignmentColumn> colunasEsperadas =  {
        colunaAlinhamentoA,
        colunaAlinhamentoB,
        colunaAlinhamentoC
    };

    const StringProblem problem("", "abc");

    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 3);
    EXPECT_EQ(result.columns, colunasEsperadas);
}

TEST(NeedlemanWunschAligner, ABCContraVazioCusta3) {

    AlignmentColumn colunaAlinhamentoA;
    colunaAlinhamentoA.xIndex = 0;

    AlignmentColumn colunaAlinhamentoB;
    colunaAlinhamentoB.xIndex = 1;

    AlignmentColumn colunaAlinhamentoC;
    colunaAlinhamentoC.xIndex = 2;

    std::vector<AlignmentColumn> colunasEsperadas =  {
        colunaAlinhamentoA,
        colunaAlinhamentoB,
        colunaAlinhamentoC
    };

    const StringProblem problem("abc", "");

    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 3);
    EXPECT_EQ(result.columns, colunasEsperadas);
}

TEST(NeedlemanWunschAligner, ABCContraABDCusta1) {
    const StringProblem problem("abc", "abd");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 1);
}

TEST(NeedlemanWunschAligner, ABCContraABXCCusta1) {

    AlignmentColumn colunaAlinhamentoA;
    colunaAlinhamentoA.xIndex = 0;
    colunaAlinhamentoA.yIndex = 0;

    AlignmentColumn colunaAlinhamentoB;
    colunaAlinhamentoB.xIndex = 1;
    colunaAlinhamentoB.yIndex = 1;

    AlignmentColumn colunaAlinhamentoC;
    colunaAlinhamentoC.yIndex = 2;

    AlignmentColumn colunaAlinhamentoD;
    colunaAlinhamentoD.xIndex = 2;
    colunaAlinhamentoD.yIndex = 3;

    std::vector<AlignmentColumn> colunasEsperadas =  {
        colunaAlinhamentoA,
        colunaAlinhamentoB,
        colunaAlinhamentoC,
        colunaAlinhamentoD
    };

    const StringProblem problem("abc", "abxc");

    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 1);
    EXPECT_EQ(result.columns, colunasEsperadas);
}

TEST(NeedlemanWunschAligner, SequenciasIguaisCustamZero) {

    AlignmentColumn colunaAlinhamentoA;
    colunaAlinhamentoA.xIndex = 0;
    colunaAlinhamentoA.yIndex = 0;

    AlignmentColumn colunaAlinhamentoB;
    colunaAlinhamentoB.xIndex = 1;
    colunaAlinhamentoB.yIndex = 1;

    AlignmentColumn colunaAlinhamentoC;
    colunaAlinhamentoC.xIndex = 2;
    colunaAlinhamentoC.yIndex = 2;

    std::vector<AlignmentColumn> colunasEsperadas =  {
        colunaAlinhamentoA,
        colunaAlinhamentoB,
        colunaAlinhamentoC
    };

    const StringProblem problem("abc", "abc");

    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 0);
    EXPECT_EQ(result.columns, colunasEsperadas);
}

TEST(NeedlemanWunschAligner, OcurranceContraOccurrenceCusta2) {
    const StringProblem problem("ocurrance", "occurrence");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 2);
}

TEST(NeedlemanWunschAligner, KittenContraSittingCusta3) {
    const StringProblem problem("kitten", "sitting");
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 3);
}

TEST(NeedlemanWunschAligner, AContraBAlpha5Delta1Custa2) {

    AlignmentColumn colunaAlinhamentoA;
    colunaAlinhamentoA.yIndex = 0;

    AlignmentColumn colunaAlinhamentoB;
    colunaAlinhamentoB.xIndex = 0;

    std::vector<AlignmentColumn> colunasEsperadas =  {
        colunaAlinhamentoA,
        colunaAlinhamentoB
    };

    const StringProblem problem("a", "b", 5, 1);
    const NeedlemanWunschAligner aligner;

    const Alignment result = aligner.align(problem);

    EXPECT_EQ(result.cost, 2);
    EXPECT_EQ(result.columns, colunasEsperadas);
}