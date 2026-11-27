#include <sstream>
#include <string>
#include <fstream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mocks.hpp"

#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/LineEdit.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/WordEdit.hpp"
#include "estrutura/terminal/TerminalUI.hpp"

using estrutura::nucleo::EditKind;
using estrutura::nucleo::LineEdit;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::WordEdit;
using estrutura::terminal::TerminalUI;

using mocks::MockDiffer;
using testing::_;
using testing::HasSubstr;
using testing::Not;
using testing::Return;

namespace {
    std::string lerArquivo(const std::string& caminho) {
        std::ifstream arquivo(caminho);
        std::ostringstream conteudo;
        conteudo << arquivo.rdbuf();
        return conteudo.str();
    }

    LineEdit linha(const EditKind kind, const std::string& antes, const std::string& depois) {
        LineEdit edit;
        edit.kind = kind;
        edit.beforeText = antes;
        edit.afterText = depois;
        return edit;
    }

    WordEdit palavra(const EditKind kind, const std::string& antes, const std::string& depois) {
        WordEdit edit;
        edit.kind = kind;
        edit.before = antes;
        edit.after = depois;
        return edit;
    }
}


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

    std::string compararDevolvendo(const TextDiff& diffDevolvido) {
        EXPECT_CALL(differ, diff(_, _)).WillOnce(Return(diffDevolvido));

        const std::string caminho1 = std::string(EXEMPLOS_DIR) + "/rascunho-1.txt";
        const std::string caminho2 = std::string(EXEMPLOS_DIR) + "/rascunho-2.txt";
        return rodar("comparar " + caminho1 + " " + caminho2 + "\n");
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

TEST_F(TerminalUITest, CompararLeOsDoisArquivosEChamaODiffer) {

    const std::string caminho1 = std::string(EXEMPLOS_DIR) + "/rascunho-1.txt";
    const std::string caminho2 = std::string(EXEMPLOS_DIR) + "/rascunho-2.txt";

    EXPECT_CALL(differ, diff(lerArquivo(caminho1), lerArquivo(caminho2))).WillOnce(Return(TextDiff{}));

    const std::string resultado = rodar("comparar " + caminho1 + " " + caminho2 + "\n");

    EXPECT_THAT(resultado, Not(HasSubstr("Não foi possível abrir")));
}

TEST_F(TerminalUITest, LinhaMantidaComDoisEspacos) {
    TextDiff diff;
    diff.lines = {linha(EditKind::Kept, "a", "a")};

    EXPECT_THAT(compararDevolvendo(diff), HasSubstr("  a\n"));
}

TEST_F(TerminalUITest, ApagadaComMenosEAdicionadaComMais) {
    TextDiff diff;
    diff.lines = {linha(EditKind::Removed, "b", ""),
    (linha(EditKind::Added, "", "c"))};

    EXPECT_THAT(compararDevolvendo(diff), HasSubstr("- b\n+ c\n"));
}