#include <cstddef>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/AlignmentDiffer.hpp"
#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/LineEdit.hpp"
#include "estrutura/nucleo/TextDiff.hpp"

#include "DiffOracle.hpp"
#include "TestFiles.hpp"

using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::AlignmentDiffer;
using estrutura::nucleo::EditKind;
using estrutura::nucleo::LineEdit;
using estrutura::nucleo::TextDiff;

class DadosReaisTest : public testing::Test {
protected:
    NeedlemanWunschAligner aligner;
    AlignmentDiffer differ{aligner};

    TextDiff compararExemplos(const std::string &antes, const std::string &depois) const {
        return differ.diff(arquivos::lerArquivo(arquivos::exemplo(antes)),
                           arquivos::lerArquivo(arquivos::exemplo(depois)));
    }
};

TEST_F(DadosReaisTest, Rascunho1Contra2TemAsMudancasEsperadas) {
    const TextDiff diff = compararExemplos("rascunho-1.txt", "rascunho-2.txt");

    ASSERT_EQ(diff.lines.size(), 15u);
    EXPECT_EQ(diff.count(EditKind::Kept), 10);
    EXPECT_EQ(diff.count(EditKind::Changed), 1);
    EXPECT_EQ(diff.count(EditKind::Added), 2);
    EXPECT_EQ(diff.count(EditKind::Removed), 2);

    EXPECT_EQ(diff.lines[3].kind, EditKind::Added);
    EXPECT_EQ(diff.lines[3].afterText, "until the morning finds me here");
}

TEST_F(DadosReaisTest, Rascunho1Contra2MostraOneVirandoTwo) {
    const TextDiff diff = compararExemplos("rascunho-1.txt", "rascunho-2.txt");
    ASSERT_GE(diff.lines.size(), 2u);

    const LineEdit &linha = diff.lines[1];
    EXPECT_EQ(linha.kind, EditKind::Changed);
    EXPECT_EQ(linha.beforeText, "I count the windows, one by one");
    EXPECT_EQ(linha.afterText, "I count the windows, two by two");

    ASSERT_EQ(linha.words.size(), 7u);
    for (const std::size_t posicao: {0u, 1u, 2u, 3u, 5u}) {
        SCOPED_TRACE("palavra " + std::to_string(posicao));
        EXPECT_EQ(linha.words[posicao].kind, EditKind::Kept);
    }
    for (const std::size_t posicao: {4u, 6u}) {
        SCOPED_TRACE("palavra " + std::to_string(posicao));
        EXPECT_EQ(linha.words[posicao].kind, EditKind::Changed);
        EXPECT_EQ(linha.words[posicao].before, "one");
        EXPECT_EQ(linha.words[posicao].after, "two");
    }
}

TEST_F(DadosReaisTest, Rascunho2Contra3TemAsMudancasEsperadas) {
    const TextDiff diff = compararExemplos("rascunho-2.txt", "rascunho-3.txt");

    ASSERT_EQ(diff.lines.size(), 14u);
    EXPECT_EQ(diff.count(EditKind::Kept), 11);
    EXPECT_EQ(diff.count(EditKind::Changed), 2);
    EXPECT_EQ(diff.count(EditKind::Added), 1);
    EXPECT_EQ(diff.count(EditKind::Removed), 0);

    EXPECT_EQ(diff.lines[8].kind, EditKind::Changed);
    EXPECT_EQ(diff.lines[8].afterText, "the last train leaves without a sound");
    EXPECT_EQ(diff.lines[10].kind, EditKind::Added);
    EXPECT_EQ(diff.lines[10].afterText, "and wear it till the colors fade");
}

TEST_F(DadosReaisTest, Rascunho2Contra3PalavraAdicionadaNoRefrao) {
    const TextDiff diff = compararExemplos("rascunho-2.txt", "rascunho-3.txt");
    ASSERT_EQ(diff.lines.size(), 14u);

    const LineEdit &linha = diff.lines[13];
    EXPECT_EQ(linha.kind, EditKind::Changed);
    EXPECT_EQ(linha.beforeText, "stay, stay until the morning");
    EXPECT_EQ(linha.afterText, "don't go, not until the morning");

    ASSERT_EQ(linha.words.size(), 6u);
    EXPECT_EQ(linha.words[0].kind, EditKind::Added);
    EXPECT_EQ(linha.words[0].before, "");
    EXPECT_EQ(linha.words[0].after, "don't");
    EXPECT_EQ(linha.words[5].kind, EditKind::Kept);
    EXPECT_EQ(linha.words[5].after, "morning");
}

TEST_F(DadosReaisTest, TodoParDeRascunhosRemontaAsDuasVersoes) {
    const std::vector<std::pair<std::string, std::string> > pares = {
        {"rascunho-1.txt", "rascunho-2.txt"},
        {"rascunho-2.txt", "rascunho-3.txt"},
        {"rascunho-1.txt", "rascunho-3.txt"},
    };

    for (const auto &[antes, depois]: pares) {
        SCOPED_TRACE(antes + " contra " + depois);
        const TextDiff diff = compararExemplos(antes, depois);

        EXPECT_EQ(oraculo::joinLines(oraculo::beforeSide(diff)) + "\n", arquivos::lerArquivo(arquivos::exemplo(antes)));
        EXPECT_EQ(oraculo::joinLines(oraculo::afterSide(diff)) + "\n", arquivos::lerArquivo(arquivos::exemplo(depois)));
        EXPECT_TRUE(oraculo::indicesAreConsecutive(diff));
    }
}

namespace {
    std::vector<std::string> arquivoGrande() {
        std::vector<std::string> linhas;
        for (int numero = 0; numero < 2000; ++numero) {
            linhas.push_back("linha " + std::to_string(numero));
        }
        return linhas;
    }

    const std::set<int> linhasEditadas = {100, 500, 900, 1300};
    const std::set<int> linhasApagadas = {300, 700, 1100};
    const std::set<int> novasLinhasAntesDe = {200, 1500, 1800};

    std::vector<std::string> arquivoGrandeEditado() {
        std::vector<std::string> linhas;
        for (int numero = 0; numero < 2000; ++numero) {
            if (novasLinhasAntesDe.count(numero) > 0) {
                linhas.push_back("uma linha nova antes da " + std::to_string(numero));
            }
            if (linhasApagadas.count(numero) > 0) {
                continue;
            }
            const std::string original = "linha " + std::to_string(numero);
            linhas.push_back(linhasEditadas.count(numero) > 0 ? original + " editada" : original);
        }
        return linhas;
    }
} // namespace

TEST_F(DadosReaisTest, ArquivoGrandeComPoucasMudancas) {
    const std::vector<std::string> antes = arquivoGrande();
    const std::vector<std::string> depois = arquivoGrandeEditado();

    const TextDiff diff = differ.diff(oraculo::joinLines(antes), oraculo::joinLines(depois));

    EXPECT_EQ(diff.count(EditKind::Kept), 1993);
    EXPECT_EQ(diff.count(EditKind::Changed), 4);
    EXPECT_EQ(diff.count(EditKind::Removed), 3);
    EXPECT_EQ(diff.count(EditKind::Added), 3);
    EXPECT_EQ(oraculo::changedLineCount(diff), 2 * 4 + 3 + 3);

    EXPECT_EQ(oraculo::beforeSide(diff), antes);
    EXPECT_EQ(oraculo::afterSide(diff), depois);
    EXPECT_TRUE(oraculo::indicesAreConsecutive(diff));
}