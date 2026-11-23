#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/nucleo/TokenAlignmentProblem.hpp"

using estrutura::nucleo::TokenAlignmentProblem;

TEST(TokenAlignmentProblem, TamanhosSaoOsDasListas) {

    const std::vector<std::string> antes = {"a", "b"};
    const std::vector<std::string> depois = {"a", "c", "d"};
    constexpr int mismatchCost = 7;
    constexpr int unmatchedCost = 2;

    const TokenAlignmentProblem problem(antes, depois, mismatchCost, unmatchedCost);

    EXPECT_EQ(problem.lengthX(), 2);
    EXPECT_EQ(problem.lengthY(), 3);
}
