#include "VersionHistory.hpp"

#include "estrutura/NotImplemented.hpp"

namespace estrutura::nucleo {
    VersionHistory::VersionHistory(IVersionStore &store, const IDiffer &differ, const IClock &clock)
        : store(store), differ(differ), clock(clock) {
    }

    std::optional<Version> VersionHistory::save(const std::string &document, const std::string &text,
                                                const std::string &message) {
        notImplemented("VersionHistory::save", document, text, message, store, clock);
    }

    std::vector<Version> VersionHistory::versions(const std::string &document) const {
        notImplemented("VersionHistory::versions", document);
    }

    TextDiff VersionHistory::diff(const std::string &document, const int fromVersion, const int toVersion) const {
        notImplemented("VersionHistory::diff", document, fromVersion, toVersion, differ);
    }

    TextDiff VersionHistory::changesSinceLatest(const std::string &document, const std::string &text) const {
        notImplemented("VersionHistory::changesSinceLatest", document, text);
    }

    std::optional<Version> VersionHistory::restore(const std::string &document, const int versionNumber) {
        notImplemented("VersionHistory::restore", document, versionNumber);
    }

    std::vector<std::string> VersionHistory::documents() const {
        notImplemented("VersionHistory::documents");
    }

    Version VersionHistory::find(const std::string &document, const int versionNumber) const {
        notImplemented("VersionHistory::find", document, versionNumber);
    }
} // namespace estrutura::nucleo