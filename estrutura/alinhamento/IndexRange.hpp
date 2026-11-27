#ifndef ESTRUTURA_ALINHAMENTO_INDEX_RANGE_H
#define ESTRUTURA_ALINHAMENTO_INDEX_RANGE_H


namespace estrutura::alinhamento {
    struct IndexRange {
        int begin = 0;

        int end = 0;

        [[nodiscard]] int length() const;

        [[nodiscard]] int middle() const;
    };
} // namespace estrutura::alinhamento
#endif