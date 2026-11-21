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
    colunaA.xIndex = 1;
    colunaA.yIndex = 0;

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
