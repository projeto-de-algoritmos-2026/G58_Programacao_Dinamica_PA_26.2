#include "TerminalUI.hpp"
#include "estrutura/nucleo/WordEdit.hpp"

#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <optional>

#include "estrutura/NotImplemented.hpp"

namespace estrutura::terminal {
    namespace {
        std::optional<std::string> readFile(const std::filesystem::path &path) {
            std::ifstream file(path);
            if (!file) { return std::nullopt; }
            std::ostringstream content;
            content << file.rdbuf();
            return content.str();
        }

        std::string formatWord(const nucleo::WordEdit &word) {
            if (word.kind == nucleo::EditKind::Kept) {
                return word.before;
            } else if (word.kind == nucleo::EditKind::Changed) {
                return "[-" + word.before + "-]{+" + word.after + "+}";
            } else if (word.kind == nucleo::EditKind::Removed) {
                return "[-" + word.before + "-]";
            }
            return "{+" + word.after + "+}";
        }
    }

    TerminalUI::TerminalUI(const nucleo::IDiffer &differ, std::istream &input, std::ostream &output)
        : differ(differ), input(input), output(output) {
    }

    void TerminalUI::run() const {
        std::string line;

        while (std::getline(input, line)) {
            std::istringstream lineStream(line);

            std::string command;
            lineStream >> command;

            if (command == "sair") { break; }

            if (command == "comparar") {
                std::filesystem::path firstPath;
                std::filesystem::path secondPath;

                lineStream >> firstPath >> secondPath;

                const std::optional<std::string> before = readFile(firstPath);
                const std::optional<std::string> after = readFile(secondPath);

                if (!before.has_value()) {
                    output << "Não foi possível abrir o arquivo: " << firstPath << "\n";
                } else if (!after.has_value()) {
                    output << "Não foi possível abrir o arquivo: " << secondPath << "\n";
                } else {
                    printDiff(differ.diff(*before, *after));
                }
            } else if (command == "") {
                // linha vazia não faz nada
            } else if (command == "ajuda") {
                output << "comparar <a> <b>	compara os arquivos a e b\n"
                        << "ajuda						esta lista\n"
                        << "sair						encerra\n";
            } else {
                output << "Comando desconhecido.\n";
            }
        }
    }

    void TerminalUI::printDiff(const nucleo::TextDiff &diff) const {
        if (diff.isIdentical()) {
            output << "Os arquivos são iguais.\n";
            return;
        }

        for (const nucleo::LineEdit &line: diff.lines) {
            if (line.kind == nucleo::EditKind::Kept) {
                output << "  " << line.beforeText << "\n";
            } else if (line.kind == nucleo::EditKind::Removed) {
                output << "- " << line.beforeText << "\n";
            } else if (line.kind == nucleo::EditKind::Added) {
                output << "+ " << line.afterText << "\n";
            } else if (line.kind == nucleo::EditKind::Changed) {
                output << "~ ";
                bool firstWord = true;
                for (const nucleo::WordEdit &word: line.words) {
                    if (!firstWord) {
                        output << " ";
                    }
                    output << formatWord(word);
                    firstWord = false;
                }
                output << "\n";
            }
        }
    }

    void TerminalUI::printVersions(const std::vector<nucleo::Version> &versions) {
        notImplemented("TerminalUI::printVersions", versions);
    }
} // namespace estrutura::terminal