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

TEST_F(TerminalUITest, AjudaListaOsComandos) {
    const std::string resultado = rodar("ajuda\n");

    EXPECT_THAT(resultado, HasSubstr("comparar"));
    EXPECT_THAT(resultado, HasSubstr("sair"));
}

TEST_F(TerminalUITest, SairEncerraMesmoComMaisComandos) {
    const std::string resultado = rodar("sair\najuda\n");

    EXPECT_THAT(resultado, Not(HasSubstr("comparar")));
}

TEST_F(TerminalUITest, ComandoDesconhecidoAvisaEContinua) {
    const std::string resultado = rodar("xyz\najuda\n");

    EXPECT_THAT(resultado, HasSubstr("desconhecido"));
    EXPECT_THAT(resultado, HasSubstr("comparar"));
}

TEST_F(TerminalUITest, LinhaVaziaNaoFazNada) {
    const std::string resultado = rodar("\n");

    EXPECT_EQ(resultado, "");
}

TEST_F(TerminalUITest, ArquivoQueNaoAbreAvisaEContinua) {
    const std::string resultado = rodar("comparar nao-existe.txt outro.txt\n");

    EXPECT_THAT(resultado, HasSubstr("Não foi possível abrir"));
}