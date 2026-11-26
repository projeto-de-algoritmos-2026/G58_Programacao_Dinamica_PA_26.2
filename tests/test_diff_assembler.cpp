#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/DiffAssembler.hpp"
#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/LineEdit.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::AlignmentColumn;
using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::DiffAssembler;
using estrutura::nucleo::EditKind;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::LineEdit;

class DiffAssemblerTest : public testing::Test {
protected:
    NeedlemanWunschAligner aligner;
    DiffAssembler assembler{aligner};

    TextDiff assemble(const std::vector<std::string>& antes, const std::vector<std::string>& depois, const std::vector<AlignmentColumn>& colunas) {
        Alignment alignment;
        alignment.columns = colunas;
        return assembler.assemble(antes, depois, alignment);
    }
};

TEST_F(DiffAssemblerTest, SemColunasNaoTemLinhas) {
    const TextDiff resultado = assemble({}, {}, {});
    EXPECT_TRUE(resultado.lines.empty());
}

TEST_F(DiffAssemblerTest, ColunaComDoisIndicesViraKept) {
    const TextDiff resultado = assemble({"a"}, {"a"}, {{0, 0}});
    ASSERT_EQ(resultado.lines.size(), 1u);

    const LineEdit& linha = resultado.lines[0];

    EXPECT_EQ(linha.kind, EditKind::Kept);
    EXPECT_EQ(linha.beforeIndex, 0);
    EXPECT_EQ(linha.afterIndex, 0);
    EXPECT_EQ(linha.beforeText, "a");
    EXPECT_EQ(linha.afterText, "a");
}

TEST_F(DiffAssemblerTest, SoIndiceAntesViraRemoved) {
    const TextDiff resultado = assemble({"a"}, {}, {{0, std::nullopt}});
    ASSERT_EQ(resultado.lines.size(), 1u);

    const LineEdit& linha = resultado.lines[0];

    EXPECT_EQ(linha.kind, EditKind::Removed);
    EXPECT_EQ(linha.beforeIndex, 0);
    EXPECT_EQ(linha.afterIndex, std::nullopt);
    EXPECT_EQ(linha.beforeText, "a");
    EXPECT_EQ(linha.afterText, "");
}

TEST_F(DiffAssemblerTest, SoIndiceDepoisViraAdded) {
    const TextDiff resultado = assemble({}, {"a"}, {{std::nullopt, 0}});
    ASSERT_EQ(resultado.lines.size(), 1u);

    const LineEdit& linha = resultado.lines[0];

    EXPECT_EQ(linha.kind, EditKind::Added);
    EXPECT_EQ(linha.beforeIndex, std::nullopt);
    EXPECT_EQ(linha.afterIndex, 0);
    EXPECT_EQ(linha.beforeText, "");
    EXPECT_EQ(linha.afterText, "a");
}

TEST_F(DiffAssemblerTest, ColunasViramLinhasNaOrdemDoTexto) {
    const TextDiff resultado = assemble({"a", "b"}, {"a", "c"}, {{0, 0}, {1, std::nullopt}, {std::nullopt, 1}});
    ASSERT_EQ(resultado.lines.size(), 3u);

    EXPECT_EQ(resultado.lines[0].kind, EditKind::Kept);

    EXPECT_EQ(resultado.lines[1].kind, EditKind::Removed);
    EXPECT_EQ(resultado.lines[1].beforeText, "b");

    EXPECT_EQ(resultado.lines[2].kind, EditKind::Added);
    EXPECT_EQ(resultado.lines[2].afterText, "c");
}

TEST_F(DiffAssemblerTest, LinhasParecidasViramChanged) {
    const TextDiff resultado = assemble({"a b c"}, {"a b d"}, {{0, std::nullopt}, {std::nullopt, 0}});
    ASSERT_EQ(resultado.lines.size(), 1u);

    const LineEdit& linha = resultado.lines[0];

    EXPECT_EQ(linha.kind, EditKind::Changed);
    EXPECT_EQ(linha.beforeIndex, 0);
    EXPECT_EQ(linha.afterIndex, 0);
    EXPECT_EQ(linha.beforeText, "a b c");
    EXPECT_EQ(linha.afterText, "a b d");
}

TEST_F(DiffAssemblerTest, ChangedGuardaAsPalavras) {
    const TextDiff resultado = assemble({"a b c"}, {"a b d"}, {{0, std::nullopt}, {std::nullopt, 0}});
    ASSERT_EQ(resultado.lines.size(), 1u);

    const LineEdit& linha = resultado.lines[0];

    ASSERT_EQ(linha.words.size(), 3u);

    EXPECT_EQ(linha.words[0].kind, EditKind::Kept);
    EXPECT_EQ(linha.words[0].before, "a");
    EXPECT_EQ(linha.words[0].after, "a");

    EXPECT_EQ(linha.words[1].kind, EditKind::Kept);
    EXPECT_EQ(linha.words[1].before, "b");
    EXPECT_EQ(linha.words[1].after, "b");

    EXPECT_EQ(linha.words[2].kind, EditKind::Changed);
    EXPECT_EQ(linha.words[2].before, "c");
    EXPECT_EQ(linha.words[2].after, "d");
}

TEST_F(DiffAssemblerTest, LinhasSemNadaEmComumContinuamSeparadas) {
    const TextDiff resultado = assemble({"a b"}, {"c d"}, {{0, std::nullopt}, {std::nullopt, 0}});
    ASSERT_EQ(resultado.lines.size(), 2u);

    EXPECT_EQ(resultado.lines[0].kind, EditKind::Removed);
    EXPECT_EQ(resultado.lines[0].beforeText, "a b");

    EXPECT_EQ(resultado.lines[1].kind, EditKind::Added);
    EXPECT_EQ(resultado.lines[1].afterText, "c d");
}

TEST_F(DiffAssemblerTest, DuasApagadasEUmaAdicionada) {
    const TextDiff resultado = assemble({"a b c", "x y z"}, {"a b d"}, {{0, std::nullopt},  {1, std::nullopt}, {std::nullopt, 0}});
    ASSERT_EQ(resultado.lines.size(), 2u);

    EXPECT_EQ(resultado.lines[0].kind, EditKind::Changed);
    EXPECT_EQ(resultado.lines[0].beforeText, "a b c");
    EXPECT_EQ(resultado.lines[0].afterText, "a b d");

    EXPECT_EQ(resultado.lines[1].kind, EditKind::Removed);
    EXPECT_EQ(resultado.lines[1].beforeText, "x y z");
}

TEST_F(DiffAssemblerTest, NuncaPareiaAtravesDeUmaKept) {
    const TextDiff resultado = assemble({"a b c", "x"}, {"x", "a b d"}, {{0, std::nullopt},  {1, 0}, {std::nullopt, 1}});
    ASSERT_EQ(resultado.lines.size(), 3u);

    EXPECT_EQ(resultado.lines[0].kind, EditKind::Removed);
    EXPECT_EQ(resultado.lines[0].beforeText, "a b c");

    EXPECT_EQ(resultado.lines[1].kind, EditKind::Kept);
    EXPECT_EQ(resultado.lines[1].beforeText, "x");
    EXPECT_EQ(resultado.lines[1].afterText, "x");

    EXPECT_EQ(resultado.lines[2].kind, EditKind::Added);
    EXPECT_EQ(resultado.lines[2].afterText, "a b d");
}

TEST_F(DiffAssemblerTest, PalavraAdicionadaGuardaODepois) {

    const TextDiff resultado = assemble({"a b"}, {"a x b"}, {{0, std::nullopt},  {std::nullopt, 0}});
    ASSERT_EQ(resultado.lines.size(), 1u);

    const LineEdit& linha = resultado.lines[0];

    ASSERT_EQ(linha.words.size(), 3u);

    EXPECT_EQ(linha.words[0].kind, EditKind::Kept);
    EXPECT_EQ(linha.words[0].before, "a");
    EXPECT_EQ(linha.words[0].after, "a");

    EXPECT_EQ(linha.words[1].kind, EditKind::Added);
    EXPECT_EQ(linha.words[1].before, "");
    EXPECT_EQ(linha.words[1].after, "x");

    EXPECT_EQ(linha.words[2].kind, EditKind::Kept);
    EXPECT_EQ(linha.words[2].before, "b");
    EXPECT_EQ(linha.words[2].after, "b");
}