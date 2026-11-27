#include "FolderVersionStore.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::adaptadores {
    FolderVersionStore::FolderVersionStore(const std::filesystem::path &root)
        : root(root) {
    }

    void FolderVersionStore::append(const std::string &document, const nucleo::Version &version) {
        notImplemented("FolderVersionStore::append", document, version, root);
    }

    std::vector<nucleo::Version> FolderVersionStore::versions(const std::string &document) const {
        notImplemented("FolderVersionStore::versions", document);
    }

    std::vector<std::string> FolderVersionStore::documents() const {
        notImplemented("FolderVersionStore::documents");
    }
} // namespace estrutura::adaptadores