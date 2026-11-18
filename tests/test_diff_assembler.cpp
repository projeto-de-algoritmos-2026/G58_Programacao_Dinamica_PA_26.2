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
