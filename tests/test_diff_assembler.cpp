#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "Mocks.hpp"

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/nucleo/DiffAssembler.hpp"
#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/LineEdit.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::AlignmentColumn;
using estrutura::nucleo::DiffAssembler;
using estrutura::nucleo::EditKind;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::LineEdit;

using mocks::MockAligner;
using testing::_;
using testing::Return;

class DiffAssemblerTest : public testing::Test {
protected:
    testing::StrictMock<MockAligner> aligner;
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