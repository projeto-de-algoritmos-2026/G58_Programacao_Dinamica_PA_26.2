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

TEST(TokenAlignmentProblem, CustoDoParVemDoConstrutor) {
    const std::vector<std::string> antes = {"a", "b"};
    const std::vector<std::string> depois = {"a", "c", "d"};
    constexpr int mismatchCost = 7;
    constexpr int unmatchedCost = 2;


    const TokenAlignmentProblem problem(antes, depois, mismatchCost, unmatchedCost);

    EXPECT_EQ(problem.pairCost(0, 0), 0);
    EXPECT_EQ(problem.pairCost(1, 1), 7);
}

TEST(TokenAlignmentProblem, CustoDaLacunaVemDoConstrutor) {
    const std::vector<std::string> antes = {"a", "b"};
    const std::vector<std::string> depois = {"a", "c", "d"};
    constexpr int mismatchCost = 7;
    constexpr int unmatchedCost = 2;


    const TokenAlignmentProblem problem(antes, depois, mismatchCost, unmatchedCost);

    EXPECT_EQ(problem.unmatchedXCost(0), 2);
    EXPECT_EQ(problem.unmatchedYCost(2), 2);
}

TEST(TokenAlignmentProblem, ForLinesUsaTresParaTrocaEUmParaLacuna) {
    const std::vector<std::string> antes = {"a", "b"};
    const std::vector<std::string> depois = {"a", "c", "d"};

    const TokenAlignmentProblem problem = TokenAlignmentProblem::forLines(antes, depois);

    EXPECT_EQ(problem.pairCost(0, 0), 0);
    EXPECT_EQ(problem.pairCost(1, 1), 3);
    EXPECT_EQ(problem.unmatchedXCost(0), 1);
    EXPECT_EQ(problem.unmatchedYCost(0), 1);
}

TEST(TokenAlignmentProblem, ForWordsUsaUmParaTrocaEUmParaLacuna) {
    const std::vector<std::string> antes = {"a", "b"};
    const std::vector<std::string> depois = {"a", "c", "d"};

    const TokenAlignmentProblem problem = TokenAlignmentProblem::forWords(antes, depois);

    EXPECT_EQ(problem.pairCost(0, 0), 0);
    EXPECT_EQ(problem.pairCost(1, 1), 1);
    EXPECT_EQ(problem.unmatchedXCost(0), 1);
    EXPECT_EQ(problem.unmatchedYCost(0), 1);
}