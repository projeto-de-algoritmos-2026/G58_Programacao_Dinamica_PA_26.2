#ifndef PROGRAMACAO_DINAMICA_G58_DIFFORACLE_HPP
#define PROGRAMACAO_DINAMICA_G58_DIFFORACLE_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "estrutura/nucleo/EditKind.hpp"
#include "estrutura/nucleo/LineEdit.hpp"
#include "estrutura/nucleo/TextDiff.hpp"

namespace oraculo {
    using estrutura::nucleo::EditKind;
    using estrutura::nucleo::LineEdit;
    using estrutura::nucleo::TextDiff;

    inline std::vector<std::string> beforeSide(const TextDiff &diff) {
        std::vector<std::string> lines;
        for (const LineEdit &line: diff.lines) {
            if (line.kind != EditKind::Added) {
                lines.push_back(line.beforeText);
            }
        }
        return lines;
    }

    inline std::vector<std::string> afterSide(const TextDiff &diff) {
        std::vector<std::string> lines;
        for (const LineEdit &line: diff.lines) {
            if (line.kind != EditKind::Removed) {
                lines.push_back(line.afterText);
            }
        }
        return lines;
    }

    inline bool indicesAreConsecutive(const TextDiff &diff) {
        int nextBeforeIndex = 0;
        int nextAfterIndex = 0;

        for (const LineEdit &line: diff.lines) {
            if (line.kind != EditKind::Added) {
                if (line.beforeIndex != nextBeforeIndex) {
                    return false;
                }
                ++nextBeforeIndex;
            } else if (line.beforeIndex.has_value()) {
                return false;
            }

            if (line.kind != EditKind::Removed) {
                if (line.afterIndex != nextAfterIndex) {
                    return false;
                }
                ++nextAfterIndex;
            } else if (line.afterIndex.has_value()) {
                return false;
            }
        }

        return true;
    }

    inline int changedLineCount(const TextDiff &diff) {
        int changes = 0;
        for (const LineEdit &line: diff.lines) {
            if (line.kind == EditKind::Removed || line.kind == EditKind::Added) {
                changes += 1;
            } else if (line.kind == EditKind::Changed) {
                changes += 2;
            }
        }
        return changes;
    }

    inline int lcsBruteForce(const std::vector<std::string> &first, const std::vector<std::string> &second,
                             const int firstLength, const int secondLength) {
        if (firstLength == 0 || secondLength == 0) {
            return 0;
        }

        int best = std::max(lcsBruteForce(first, second, firstLength - 1, secondLength),
                            lcsBruteForce(first, second, firstLength, secondLength - 1));

        if (first[firstLength - 1] == second[secondLength - 1]) {
            best = std::max(best, 1 + lcsBruteForce(first, second, firstLength - 1, secondLength - 1));
        }

        return best;
    }

    inline int lcsBruteForce(const std::vector<std::string> &first, const std::vector<std::string> &second) {
        return lcsBruteForce(first, second, static_cast<int>(first.size()), static_cast<int>(second.size()));
    }

    inline std::string joinLines(const std::vector<std::string> &lines) {
        std::string text;
        for (std::size_t position = 0; position < lines.size(); ++position) {
            if (position > 0) {
                text += '\n';
            }
            text += lines[position];
        }
        return text;
    }
} // namespace oraculo

#endif //PROGRAMACAO_DINAMICA_G58_DIFFORACLE_HPP