#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/nucleo/TokenAlignmentProblem.hpp"

using estrutura::nucleo::TokenAlignmentProblem;

class TokenAlignmentProblemTest : public ::testing::Test {
protected:
    const std::vector<std::string> antes = {"a", "b"};
    const std::vector<std::string> depois = {"a", "c", "d"};
    static constexpr int mismatchCost = 7;
    static constexpr int unmatchedCost = 2;

    const TokenAlignmentProblem problem{antes, depois, mismatchCost, unmatchedCost};
};

TEST_F(TokenAlignmentProblemTest, TamanhosSaoOsDasListas) {
    EXPECT_EQ(problem.lengthX(), 2);
    EXPECT_EQ(problem.lengthY(), 3);
}

TEST_F(TokenAlignmentProblemTest, CustoDoParVemDoConstrutor) {
    EXPECT_EQ(problem.pairCost(0, 0), 0);
    EXPECT_EQ(problem.pairCost(1, 1), mismatchCost);
}

TEST_F(TokenAlignmentProblemTest, CustoDaLacunaVemDoConstrutor) {
    EXPECT_EQ(problem.unmatchedXCost(0), unmatchedCost);
    EXPECT_EQ(problem.unmatchedYCost(2), unmatchedCost);
}

TEST_F(TokenAlignmentProblemTest, ForLinesUsaTresParaTrocaEUmParaLacuna) {
    const TokenAlignmentProblem linhas = TokenAlignmentProblem::forLines(antes, depois);

    EXPECT_EQ(linhas.pairCost(0, 0), 0);
    EXPECT_EQ(linhas.pairCost(1, 1), 3);
    EXPECT_EQ(linhas.unmatchedXCost(0), 1);
    EXPECT_EQ(linhas.unmatchedYCost(0), 1);
}

TEST_F(TokenAlignmentProblemTest, ForWordsUsaUmParaTrocaEUmParaLacuna) {
    const TokenAlignmentProblem palavras = TokenAlignmentProblem::forWords(antes, depois);

    EXPECT_EQ(palavras.pairCost(0, 0), 0);
    EXPECT_EQ(palavras.pairCost(1, 1), 1);
    EXPECT_EQ(palavras.unmatchedXCost(0), 1);
    EXPECT_EQ(palavras.unmatchedYCost(0), 1);
}