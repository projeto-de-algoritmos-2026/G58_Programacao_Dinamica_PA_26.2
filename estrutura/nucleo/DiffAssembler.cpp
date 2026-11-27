#include <algorithm>
#include <cstddef>

#include "DiffAssembler.hpp"
#include "estrutura/nucleo/TextSplitter.hpp"
#include "estrutura/nucleo/TokenAlignmentProblem.hpp"
#include "estrutura/alinhamento/IAligner.hpp"

namespace estrutura::nucleo {
    namespace {
        bool areSimilar(const std::vector<WordEdit> &words) {
            int keptCount = 0;
            int beforeCount = 0;
            int afterCount = 0;

            for (const WordEdit &word: words) {
                if (word.kind == EditKind::Kept) {
                    keptCount++;
                }
                if (word.kind != EditKind::Added) {
                    beforeCount++;
                }
                if (word.kind != EditKind::Removed) {
                    afterCount++;
                }
            }

            return 2 * keptCount >= std::max(beforeCount, afterCount);
        }
    } // namespace

    DiffAssembler::DiffAssembler(const alinhamento::IAligner &aligner)
        : aligner(aligner) {
    }

    TextDiff DiffAssembler::assemble(const std::vector<std::string> &beforeLines,
                                     const std::vector<std::string> &afterLines,
                                     const alinhamento::Alignment &lineAlignment) const {
        std::vector<LineEdit> lines;
        for (const alinhamento::AlignmentColumn &column: lineAlignment.columns) {
            LineEdit line;
            line.beforeIndex = column.xIndex;
            line.afterIndex = column.yIndex;

            if (column.xIndex.has_value() && column.yIndex.has_value()) {
                line.kind = EditKind::Kept;
                line.beforeText = beforeLines.at(*column.xIndex);
                line.afterText = afterLines.at(*column.yIndex);
            } else if (column.xIndex.has_value()) {
                line.kind = EditKind::Removed;
                line.beforeText = beforeLines.at(*column.xIndex);
            } else {
                line.kind = EditKind::Added;
                line.afterText = afterLines.at(*column.yIndex);
            }

            lines.push_back(line);
        }

        TextDiff result;
        std::vector<LineEdit> removedBlock;
        std::vector<LineEdit> addedBlock;

        for (const LineEdit &line: lines) {
            if (line.kind == EditKind::Removed) {
                removedBlock.push_back(line);
            } else if (line.kind == EditKind::Added) {
                addedBlock.push_back(line);
            } else {
                closeBlock(removedBlock, addedBlock, result.lines);
                result.lines.push_back(line);
            }
        }
        closeBlock(removedBlock, addedBlock, result.lines);

        return result;
    }

    void DiffAssembler::closeBlock(std::vector<LineEdit>& removed,std::vector<LineEdit>& added, std::vector<LineEdit>& output) const {

        const std::size_t pairCount = std::max(removed.size(), added.size());

        for (std::size_t position = 0; position < pairCount; position++) {
            const bool hasRemoved = position < removed.size();
            const bool hasAdded = position < added.size();

            if (hasRemoved && hasAdded) {
                const std::vector<WordEdit> words = wordEdits(removed[position].beforeText,
                                                              added[position].afterText);

                if (areSimilar(words)) {
                    LineEdit changed;
                    changed.kind = EditKind::Changed;
                    changed.beforeIndex = removed[position].beforeIndex;
                    changed.afterIndex = added[position].afterIndex;
                    changed.beforeText = removed[position].beforeText;
                    changed.afterText = added[position].afterText;
                    changed.words = words;
                    output.push_back(changed);
                    continue;
                }
            }
            if (hasRemoved) {
                output.push_back(removed[position]);
            }
            if (hasAdded) {
                output.push_back(added[position]);
            }
        }
        removed.clear();
        added.clear();
    }

    std::vector<WordEdit> DiffAssembler::wordEdits(const std::string &beforeLine, const std::string &afterLine) const {
        const std::vector<std::string> beforeWords = TextSplitter::words(beforeLine);
        const std::vector<std::string> afterWords = TextSplitter::words(afterLine);


        const TokenAlignmentProblem wordProblem = TokenAlignmentProblem::forWords(beforeWords, afterWords);

        const alinhamento::Alignment wordAlignment = aligner.align(wordProblem);

        std::vector<WordEdit> result;

        for (const alinhamento::AlignmentColumn &column: wordAlignment.columns) {
            WordEdit wordEdit;

            if (column.xIndex.has_value() && column.yIndex.has_value()) {
                wordEdit.before = beforeWords.at(*column.xIndex);
                wordEdit.after = afterWords.at(*column.yIndex);
                wordEdit.kind = wordEdit.before == wordEdit.after ? EditKind::Kept : EditKind::Changed;
            } else if (column.xIndex.has_value()) {
                wordEdit.kind = EditKind::Removed;
                wordEdit.before = beforeWords.at(*column.xIndex);
            } else {
                wordEdit.kind = EditKind::Added;
                wordEdit.after = afterWords.at(*column.yIndex);
            }

            result.push_back(wordEdit);
        }

        return result;
    }
} // namespace estrutura::nucleo