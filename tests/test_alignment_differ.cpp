#include <string>

#include <gtest/gtest.h>

#include "Mocks.hpp"

#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/AlignmentDiffer.hpp"
#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/TextDiff.hpp"

using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::AlignmentDiffer;
using estrutura::nucleo::EditKind;
using estrutura::nucleo::TextDiff;

using mocks::MockAligner;
using testing::_;
using testing::Return;

class AlignmentDifferTest : public testing::Test {
protected:
    NeedlemanWunschAligner aligner;
    AlignmentDiffer differ{aligner};
};

TEST_F(AlignmentDifferTest, TextosIguaisSoTemLinhasKept) {

    const TextDiff resultado = differ.diff("a\nb", "a\nb");

    ASSERT_EQ(resultado.lines.size(), 2u);

    EXPECT_EQ(resultado.lines[0].kind, EditKind::Kept);
    EXPECT_EQ(resultado.lines[1].kind, EditKind::Kept);

    EXPECT_TRUE(resultado.isIdentical());

}

TEST_F(AlignmentDifferTest, AntesVazioTudoAdded) {

    const TextDiff resultado = differ.diff("", "a\nb");

    ASSERT_EQ(resultado.lines.size(), 2u);

    EXPECT_EQ(resultado.lines[0].kind, EditKind::Added);
    EXPECT_EQ(resultado.lines[1].kind, EditKind::Added);

}

TEST_F(AlignmentDifferTest, DepoisVazioTudoRemoved) {

    const TextDiff resultado = differ.diff("a\nb", "");

    ASSERT_EQ(resultado.lines.size(), 2u);

    EXPECT_EQ(resultado.lines[0].kind, EditKind::Removed);
    EXPECT_EQ(resultado.lines[1].kind, EditKind::Removed);

}
