#ifndef ESTRUTURA_NUCLEO_I_VERSION_HISTORY_H
#define ESTRUTURA_NUCLEO_I_VERSION_HISTORY_H

#include <optional>
#include <string>
#include <vector>

#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/Version.hpp"

namespace estrutura::nucleo {
class IVersionHistory {
public:
	virtual ~IVersionHistory() = default;

	virtual std::optional<Version> save(const std::string& document, const std::string& text, const std::string& message) = 0;

	[[nodiscard]] virtual std::vector<Version> versions(const std::string& document) const = 0;

	[[nodiscard]] virtual TextDiff diff(const std::string& document, int fromVersion, int toVersion) const = 0;

	[[nodiscard]] virtual TextDiff changesSinceLatest(const std::string& document, const std::string& text) const = 0;

	virtual std::optional<Version> restore(const std::string& document, int versionNumber) = 0;

	[[nodiscard]] virtual std::vector<std::string> documents() const = 0;

};

}  // namespace estrutura::nucleo
#endif
