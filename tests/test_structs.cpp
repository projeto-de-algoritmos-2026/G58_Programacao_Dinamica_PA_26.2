#include <optional>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/AlignmentColumn.hpp"
#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/LineEdit.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/WordEdit.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::AlignmentColumn;
using estrutura::nucleo::EditKind;
using estrutura::nucleo::LineEdit;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::WordEdit;

TEST(AlignmentColumn, MesmosIndicesSaoIguais) {

    AlignmentColumn colunaA;
    colunaA.xIndex = 1;
    colunaA.yIndex = 1;

    AlignmentColumn colunaB;
    colunaB.xIndex = 1;
    colunaB.yIndex = 1;

    EXPECT_TRUE(colunaA == colunaB);
}

TEST(AlignmentColumn, LacunaEmXDiferenteDeIndiceZero) {

    AlignmentColumn colunaA;
    colunaA.xIndex = 0;
    colunaA.yIndex = 1;

    AlignmentColumn colunaB;
    colunaB.yIndex = 1;

    EXPECT_FALSE(colunaA == colunaB);
}

TEST(AlignmentColumn, LacunaEmYDiferenteDeIndiceZero) {

    AlignmentColumn colunaA;
    colunaA.xIndex = 1;
    colunaA.yIndex = 0;

    AlignmentColumn colunaB;
    colunaB.xIndex = 1;

    EXPECT_FALSE(colunaA == colunaB);
}

TEST(TextDiff, UmaKeptDuasAdded) {

    LineEdit lineEditA;
    lineEditA.kind = EditKind::Kept;

    LineEdit lineEditB;
    lineEditB.kind = EditKind::Added;

    LineEdit lineEditC;
    lineEditC.kind = EditKind::Added;

    TextDiff textDiff;
    textDiff.lines = {
        lineEditA,
        lineEditB,
        lineEditC
    };

    EXPECT_EQ(textDiff.count(EditKind::Kept), 1);
    EXPECT_EQ(textDiff.count(EditKind::Added), 2);
    EXPECT_EQ(textDiff.count(EditKind::Removed), 0);

}

TEST(TextDiff, SoLinhasKept) {

    LineEdit lineEditA;
    lineEditA.kind = EditKind::Kept;

    LineEdit lineEditB;
    lineEditB.kind = EditKind::Kept;

    LineEdit lineEditC;
    lineEditC.kind = EditKind::Kept;

    TextDiff textDiff;
    textDiff.lines = {
        lineEditA,
        lineEditB,
        lineEditC
    };

    EXPECT_TRUE(textDiff.isIdentical());

}

TEST(TextDiff, UmaKeptNoMeioDeDuasAdded) {

    LineEdit lineEditA;
    lineEditA.kind = EditKind::Added;

    LineEdit lineEditB;
    lineEditB.kind = EditKind::Kept;

    LineEdit lineEditC;
    lineEditC.kind = EditKind::Added;

    TextDiff textDiff;
    textDiff.lines = {
        lineEditA,
        lineEditB,
        lineEditC
    };

    EXPECT_FALSE(textDiff.isIdentical());

}

TEST(TextDiff, DiffSemNenhumaLinha) {

    TextDiff textDiff;
    textDiff.lines = { };

    EXPECT_TRUE(textDiff.isIdentical());

}

TEST(TextDiff, UmaAddedNoMeioDeDuasKept) {

    LineEdit lineEditA;
    lineEditA.kind = EditKind::Kept;

    LineEdit lineEditB;
    lineEditB.kind = EditKind::Added;

    LineEdit lineEditC;
    lineEditC.kind = EditKind::Kept;

    TextDiff textDiff;
    textDiff.lines = {
        lineEditA,
        lineEditB,
        lineEditC
    };

    EXPECT_FALSE(textDiff.isIdentical());

}
