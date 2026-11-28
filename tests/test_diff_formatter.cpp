#include <string>

#include <gtest/gtest.h>

#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/terminal/DiffFormatter.hpp"

using estrutura::nucleo::EditKind;
using estrutura::nucleo::LineEdit;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::WordEdit;
using estrutura::terminal::DiffFormatter;

namespace  {
    LineEdit linha(const EditKind kind, const std::string &antes, const std::string &depois) {
        LineEdit edit;
        edit.kind = kind;
        edit.beforeText = antes;
        edit.afterText = depois;
        return edit;
    }

    WordEdit palavra(const EditKind kind, const std::string &antes, const std::string &depois) {
        WordEdit edit;
        edit.kind = kind;
        edit.before = antes;
        edit.after = depois;
        return edit;
    }
}

TEST(DiffFormatter, ApagadaComMenosEAdicionadaComMais) {
    TextDiff diff;
    diff.lines = {linha(EditKind::Kept, "a", "a"),
                     linha(EditKind::Removed, "b", ""),
                     linha(EditKind::Added, "", "c")};

    EXPECT_EQ(DiffFormatter::format(diff), "  a\n- b\n+ c\n");
}

TEST(DiffFormatter, LinhaMantidaComDoisEspaços) {
    TextDiff diff;
    diff.lines = {linha(EditKind::Kept, "a", "a"),
                    linha(EditKind::Added, "", "b")};

    EXPECT_EQ(DiffFormatter::format(diff), "  a\n+ b\n");
}