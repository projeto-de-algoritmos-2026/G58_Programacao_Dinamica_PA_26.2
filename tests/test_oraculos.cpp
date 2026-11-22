#include <optional>
#include <random>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/AlignmentDiffer.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/TextSplitter.hpp"
#include "estrutura/nucleo/TokenAlignmentProblem.hpp"

#include "AlignmentOracle.hpp"
#include "RandomProblem.hpp"
#include "StringProblem.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::AlignmentColumn;
using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::AlignmentDiffer;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::TextSplitter;
using estrutura::nucleo::TokenAlignmentProblem;


TEST(AlignmentOracle, AlinhamentoCertoEValido) {
    const StringProblem problem("abc", "abxc");
    const std::vector<AlignmentColumn> columns = {{0, 0}, {1, 1}, {std::nullopt, 2}, {2, 3}};

    EXPECT_TRUE(oraculo::isValid(problem, columns));
}

TEST(AlignmentOracle, NenhumaColunaEValidaQuandoOsDoisSaoVazios) {
    const StringProblem problem("", "");

    EXPECT_TRUE(oraculo::isValid(problem, {}));
}

TEST(AlignmentOracle, ColunaDeLacunaContraLacunaEInvalida) {
    const StringProblem problem("a", "a");
    const std::vector<AlignmentColumn> columns = {{0, 0}, {std::nullopt, std::nullopt}};

    EXPECT_FALSE(oraculo::isValid(problem, columns));
}

TEST(AlignmentOracle, IndiceRepetidoEInvalido) {
    const StringProblem problem("ab", "b");
    const std::vector<AlignmentColumn> columns = {{0, std::nullopt}, {0, 0}, {1, std::nullopt}};

    EXPECT_FALSE(oraculo::isValid(problem, columns));
}

TEST(AlignmentOracle, IndiceFaltandoEInvalido) {
    const StringProblem problem("abc", "abc");
    const std::vector<AlignmentColumn> columns = {{0, 0}, {1, 1}};

    EXPECT_FALSE(oraculo::isValid(problem, columns));
}

TEST(AlignmentOracle, ColunasCruzadasSaoInvalidas) {
    const StringProblem problem("ab", "ba");
    const std::vector<AlignmentColumn> columns = {{0, 1}, {1, 0}};

    EXPECT_FALSE(oraculo::isValid(problem, columns));
}

TEST(AlignmentOracle, CustoRecalculadoSomaOCustoDeCadaColuna) {
    const ExplicitCostProblem problem({{7, 2}, {4, 9}}, {1, 3}, {5, 6});
    // y0 sozinho custa 5, o par (x0, y1) custa 2 e x1 sozinho custa 3.
    const std::vector<AlignmentColumn> columns = {{std::nullopt, 0}, {0, 1}, {1, std::nullopt}};

    ASSERT_TRUE(oraculo::isValid(problem, columns));
    EXPECT_EQ(oraculo::recomputedCost(problem, columns), 10);
}

TEST(AlignmentOracle, ForcaBrutaAcertaOsExemplosPequenos) {
    EXPECT_EQ(oraculo::bruteForceCost(StringProblem("", "")), 0);
    EXPECT_EQ(oraculo::bruteForceCost(StringProblem("", "abc")), 3);
    EXPECT_EQ(oraculo::bruteForceCost(StringProblem("abc", "abd")), 1);
    EXPECT_EQ(oraculo::bruteForceCost(StringProblem("abc", "abxc")), 1);
    EXPECT_EQ(oraculo::bruteForceCost(StringProblem("kitten", "sitting")), 3);
    EXPECT_EQ(oraculo::bruteForceCost(StringProblem("a", "b", 5, 1)), 2);
}

TEST(NeedlemanWunschContraForcaBruta, TextosSorteadosComAlphaEDeltaSorteados) {
    RandomProblemGenerator sorteio(2026);
    const NeedlemanWunschAligner aligner;

    for (int caso = 0; caso < 500; ++caso) {
        const std::string x = sorteio.text(6, "abc");
        const std::string y = sorteio.text(6, "abc");
        const int mismatchCost = sorteio.between(0, 6);
        const int unmatchedCost = sorteio.between(1, 3);
        const StringProblem problem(x, y, mismatchCost, unmatchedCost);
        SCOPED_TRACE("caso " + std::to_string(caso) + ": x = \"" + x + "\", y = \"" + y + "\", alpha = "
                     + std::to_string(mismatchCost) + ", delta = " + std::to_string(unmatchedCost));

        const Alignment result = aligner.align(problem);

        ASSERT_EQ(result.cost, oraculo::bruteForceCost(problem));
        ASSERT_TRUE(oraculo::isValid(problem, result.columns));
        ASSERT_EQ(oraculo::recomputedCost(problem, result.columns), result.cost);
    }
}

TEST(NeedlemanWunschContraForcaBruta, CustoSorteadoParaCadaParECadaLacuna) {
    RandomProblemGenerator sorteio(58);
    const NeedlemanWunschAligner aligner;

    for (int caso = 0; caso < 500; ++caso) {
        const ExplicitCostProblem problem = sorteio.explicitCostProblem(6, 9);
        SCOPED_TRACE("caso " + std::to_string(caso) + ": lengthX = " + std::to_string(problem.lengthX())
                     + ", lengthY = " + std::to_string(problem.lengthY()));

        const Alignment result = aligner.align(problem);

        ASSERT_EQ(result.cost, oraculo::bruteForceCost(problem));
        ASSERT_TRUE(oraculo::isValid(problem, result.columns));
        ASSERT_EQ(oraculo::recomputedCost(problem, result.columns), result.cost);
    }
}
