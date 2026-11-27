#include <optional>
#include <random>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/AlignmentDiffer.hpp"
#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/LineEdit.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/TextSplitter.hpp"
#include "estrutura/nucleo/TokenAlignmentProblem.hpp"

#include "AlignmentOracle.hpp"
#include "DiffOracle.hpp"
#include "RandomProblem.hpp"
#include "StringProblem.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::AlignmentColumn;
using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::AlignmentDiffer;
using estrutura::nucleo::EditKind;
using estrutura::nucleo::LineEdit;
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

namespace {
    LineEdit diffLine(const EditKind kind, const std::optional<int> beforeIndex, const std::optional<int> afterIndex,
                      const std::string &beforeText, const std::string &afterText) {
        LineEdit line;
        line.kind = kind;
        line.beforeIndex = beforeIndex;
        line.afterIndex = afterIndex;
        line.beforeText = beforeText;
        line.afterText = afterText;
        return line;
    }

    // "a" mantida, "b" apagada, "c" adicionada e "d" trocada por "e".
    TextDiff umDiffDeCadaTipo() {
        TextDiff diff;
        diff.lines = {
            diffLine(EditKind::Kept, 0, 0, "a", "a"),
            diffLine(EditKind::Removed, 1, std::nullopt, "b", ""),
            diffLine(EditKind::Added, std::nullopt, 1, "", "c"),
            diffLine(EditKind::Changed, 2, 2, "d", "e"),
        };
        return diff;
    }
} // namespace

TEST(DiffOracle, CadaLadoJuntaAsLinhasQueExistemNele) {
    const TextDiff diff = umDiffDeCadaTipo();

    EXPECT_EQ(oraculo::beforeSide(diff), (std::vector<std::string>{"a", "b", "d"}));
    EXPECT_EQ(oraculo::afterSide(diff), (std::vector<std::string>{"a", "c", "e"}));
}

TEST(DiffOracle, IndicesEmSequenciaSaoAceitos) {
    EXPECT_TRUE(oraculo::indicesAreConsecutive(umDiffDeCadaTipo()));
}

TEST(DiffOracle, IndicePuladoERecusado) {
    TextDiff diff = umDiffDeCadaTipo();
    diff.lines[1].beforeIndex = 2;

    EXPECT_FALSE(oraculo::indicesAreConsecutive(diff));
}

TEST(DiffOracle, IndiceNoLadoQueNaoExisteERecusado) {
    TextDiff diff = umDiffDeCadaTipo();
    diff.lines[2].beforeIndex = 1;

    EXPECT_FALSE(oraculo::indicesAreConsecutive(diff));
}

TEST(DiffOracle, LinhaTrocadaContaComoUmaApagadaEUmaAdicionada) {
    EXPECT_EQ(oraculo::changedLineCount(umDiffDeCadaTipo()), 4);
}

TEST(DiffOracle, ForcaBrutaDaMaiorSubsequenciaComum) {
    EXPECT_EQ(oraculo::lcsBruteForce({}, {}), 0);
    EXPECT_EQ(oraculo::lcsBruteForce({"a", "b", "c"}, {"a", "c"}), 2);
    EXPECT_EQ(oraculo::lcsBruteForce({"a", "b"}, {"c", "d"}), 0);
    EXPECT_EQ(oraculo::lcsBruteForce({"a", "b", "a"}, {"b", "a", "a"}), 2);
}

TEST(DiffOracle, JuntarLinhasDesfazOTextSplitter) {
    const std::vector<std::string> linhas = {"a", "b", "a"};

    EXPECT_EQ(oraculo::joinLines(linhas), "a\nb\na");
    EXPECT_EQ(oraculo::joinLines({}), "");
    EXPECT_EQ(TextSplitter::lines(oraculo::joinLines(linhas)), linhas);
}

namespace {
    const std::vector<std::string> vocabularioDeLinhas = {"a", "b", "c", "d"};

    std::string descrever(const std::vector<std::string> &linhas) {
        std::string texto;
        for (std::size_t posicao = 0; posicao < linhas.size(); ++posicao) {
            texto += (posicao > 0 ? " | " : "") + linhas[posicao];
        }
        return "[" + texto + "]";
    }
} // namespace

TEST(AlignmentDifferContraOraculo, ReconstroiAsDuasVersoes) {
    RandomProblemGenerator sorteio(2611);
    const NeedlemanWunschAligner aligner;
    const AlignmentDiffer differ(aligner);

    for (int caso = 0; caso < 500; ++caso) {
        const std::vector<std::string> antes = sorteio.lines(8, vocabularioDeLinhas);
        const std::vector<std::string> depois = sorteio.lines(8, vocabularioDeLinhas);
        SCOPED_TRACE(
            "caso " + std::to_string(caso) + ": antes = " + descrever(antes) + ", depois = " + descrever(depois));

        const TextDiff diff = differ.diff(oraculo::joinLines(antes), oraculo::joinLines(depois));

        ASSERT_EQ(oraculo::beforeSide(diff), antes);
        ASSERT_EQ(oraculo::afterSide(diff), depois);
        ASSERT_TRUE(oraculo::indicesAreConsecutive(diff));
    }
}

TEST(AlignmentDifferContraOraculo, FazOMinimoDeMudancas) {
    RandomProblemGenerator sorteio(2411);
    const NeedlemanWunschAligner aligner;
    const AlignmentDiffer differ(aligner);

    for (int caso = 0; caso < 500; ++caso) {
        const std::vector<std::string> antes = sorteio.lines(8, vocabularioDeLinhas);
        const std::vector<std::string> depois = sorteio.lines(8, vocabularioDeLinhas);
        SCOPED_TRACE(
            "caso " + std::to_string(caso) + ": antes = " + descrever(antes) + ", depois = " + descrever(depois));

        const TextDiff diff = differ.diff(oraculo::joinLines(antes), oraculo::joinLines(depois));
        const int totalDeLinhas = static_cast<int>(antes.size() + depois.size());

        ASSERT_EQ(oraculo::changedLineCount(diff), totalDeLinhas - 2 * oraculo::lcsBruteForce(antes, depois));
    }
}