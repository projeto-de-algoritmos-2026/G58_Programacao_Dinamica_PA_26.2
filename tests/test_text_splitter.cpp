#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/nucleo/TextSplitter.hpp"

using estrutura::nucleo::TextSplitter;

TEST(TextSplitter, TextoVazioNaoTemLinhas) {

    const std::vector<std::string> resultado = TextSplitter::lines("");

    EXPECT_TRUE(resultado.empty());
}

TEST(TextSplitter, DuasLinhasSemQuebraNoFim) {

    const std::vector<std::string> resultado = TextSplitter::lines("a\nb");

    const std::vector<std::string> esperado = {"a", "b"};

    EXPECT_EQ(resultado, esperado);
}

TEST(TextSplitter, QuebraNoFimNaoCriaLinhaVazia) {

    const std::vector<std::string> resultado = TextSplitter::lines("a\nb\n");

    const std::vector<std::string> esperado = {"a", "b"};

    EXPECT_EQ(resultado, esperado);
}

TEST(TextSplitter, LinhaEmBrancoNoMeioMantida) {

    const std::vector<std::string> resultado = TextSplitter::lines("a\n\nb");

    const std::vector<std::string> esperado = {"a", "", "b"};

    EXPECT_EQ(resultado, esperado);
}

TEST(TextSplitter, QuebraDoWindowsViraQuebraComum) {

    const std::vector<std::string> resultado = TextSplitter::lines("a\r\nb\r\n");

    const std::vector<std::string> esperado = {"a","b"};

    EXPECT_EQ(resultado, esperado);
}

TEST(TextSplitter, LinhaVaziaRetornaNenhumaPalavra) {

    const std::vector<std::string> resultado = TextSplitter::words("");

    const std::vector<std::string> esperado = {};

    EXPECT_EQ(resultado, esperado);
}

TEST(TextSplitter, PalavrasSeparadasPorEspaco) {

    const std::vector<std::string> resultado = TextSplitter::words("one two");

    const std::vector<std::string> esperado = {"one", "two"};

    EXPECT_EQ(resultado, esperado);
}