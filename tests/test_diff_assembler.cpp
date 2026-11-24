#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "Mocks.hpp"

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/nucleo/DiffAssembler.hpp"
#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/TextDiff.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::AlignmentColumn;
using estrutura::nucleo::DiffAssembler;
using estrutura::nucleo::EditKind;
using estrutura::nucleo::TextDiff;

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