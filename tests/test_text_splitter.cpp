#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "estrutura/nucleo/TextSplitter.hpp"

using estrutura::nucleo::TextSplitter;

TEST(TextSplitter, TextoVazioNaoTemLinhas) {

    const std::vector<std::string> resultado = TextSplitter::lines("");

    EXPECT_TRUE(resultado.empty());
}