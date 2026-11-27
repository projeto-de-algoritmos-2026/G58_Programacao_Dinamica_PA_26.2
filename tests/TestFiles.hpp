#ifndef PROGRAMACAO_DINAMICA_G58_TESTFILES_HPP
#define PROGRAMACAO_DINAMICA_G58_TESTFILES_HPP

#include <fstream>
#include <sstream>
#include <string>

namespace arquivos {

    inline std::string exemplo(const std::string& nome) {
        return std::string(EXEMPLOS_DIR) + "/" + nome;
    }

    inline std::string lerArquivo(const std::string& caminho) {
        std::ifstream arquivo(caminho);
        std::ostringstream conteudo;
        conteudo << arquivo.rdbuf();
        return conteudo.str();
    }

}  // namespace arquivos

#endif //PROGRAMACAO_DINAMICA_G58_TESTFILES_HPP
