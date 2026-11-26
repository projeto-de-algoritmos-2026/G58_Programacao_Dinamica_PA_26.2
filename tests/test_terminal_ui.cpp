#include <sstream>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mocks.hpp"

#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/LineEdit.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/terminal/TerminalUI.hpp"

using estrutura::nucleo::EditKind;
using estrutura::nucleo::LineEdit;
using estrutura::nucleo::TextDiff;
using estrutura::terminal::TerminalUI;

using mocks::MockDiffer;
using testing::_;
using testing::HasSubstr;
using testing::Not;
using testing::Return;


class TerminalUITest : public testing::Test {
protected:
    testing::StrictMock<MockDiffer> differ;
    std::ostringstream saida;

    std::string rodar(const std::string& comandos) {
        std::istringstream entrada(comandos);
        const TerminalUI terminal(differ, entrada, saida);
        terminal.run();
        return saida.str();
    }
};

TEST_F(TerminalUITest, FimDaEntradaEncerra) {
    const std::string resultado = rodar("");
    EXPECT_THAT(resultado, Not(HasSubstr("desconhecido")));

}