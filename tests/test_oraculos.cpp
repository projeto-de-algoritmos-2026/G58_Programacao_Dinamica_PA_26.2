#include <random>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/AlignmentDiffer.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/TextSplitter.hpp"
#include "estrutura/nucleo/TokenAlignmentProblem.hpp"

using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::AlignmentDiffer;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::TextSplitter;
using estrutura::nucleo::TokenAlignmentProblem;
