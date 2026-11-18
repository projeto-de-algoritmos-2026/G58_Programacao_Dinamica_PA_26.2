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
