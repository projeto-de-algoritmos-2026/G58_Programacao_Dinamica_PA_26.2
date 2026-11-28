#include "DiffFormatter.hpp"
#include "estrutura/nucleo/WordEdit.hpp"

#include <sstream>

namespace estrutura::terminal {
    namespace {
        std::string formatWord(const nucleo::WordEdit &word) {
            switch (word.kind) {
                case nucleo::EditKind::Kept:
                    return word.before;
                case nucleo::EditKind::Changed:
                    return "[-" + word.before + "-]{+" + word.after + "+}";
                case nucleo::EditKind::Removed:
                    return "[-" + word.before + "-]";
                case nucleo::EditKind::Added:
                    return "{+" + word.after + "+}";
            }
            return "";
        }
    }

    std::string DiffFormatter::format(const nucleo::TextDiff &diff) {
        std::ostringstream text;

        if (diff.isIdentical()) {
            text << "Os arquivos são iguais.\n";
        }

        for (const nucleo::LineEdit &line: diff.lines) {
            switch (line.kind) {
                case nucleo::EditKind::Kept:
                    text << "  " << line.beforeText << "\n";
                    break;
                case nucleo::EditKind::Removed:
                    text << "- " << line.beforeText << "\n";
                    break;
                case nucleo::EditKind::Added:
                    text << "+ " << line.afterText << "\n";
                    break;
                case nucleo::EditKind::Changed: {
                    text << "~ ";
                    bool firstWord = true;
                    for (const nucleo::WordEdit &word: line.words) {
                        if (!firstWord) {
                            text << " ";
                        }
                        text << formatWord(word);
                        firstWord = false;
                    }
                    text << "\n";
                    break;
                }
            }
        }

        return text.str();
    }
}
