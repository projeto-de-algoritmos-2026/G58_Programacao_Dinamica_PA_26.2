#ifndef ESTRUTURA_ADAPTADORES_FOLDER_VERSION_STORE_H
#define ESTRUTURA_ADAPTADORES_FOLDER_VERSION_STORE_H

#include <filesystem>
#include <string>
#include <vector>

#include "estrutura/nucleo/IVersionStore.hpp"
#include "estrutura/nucleo/Version.hpp"

namespace estrutura::adaptadores {
    class FolderVersionStore : public nucleo::IVersionStore {
        std::filesystem::path root;

    public:
        explicit FolderVersionStore(const std::filesystem::path &root);

        void append(const std::string &document, const nucleo::Version &version) override;

        [[nodiscard]] std::vector<nucleo::Version> versions(const std::string &document) const override;

        [[nodiscard]] std::vector<std::string> documents() const override;
    };
} // namespace estrutura::adaptadores
#endif