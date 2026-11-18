#ifndef ESTRUTURA_NUCLEO_VERSION_HISTORY_H
#define ESTRUTURA_NUCLEO_VERSION_HISTORY_H

#include <optional>
#include <string>
#include <vector>

#include "estrutura/nucleo/IClock.hpp"
#include "estrutura/nucleo/IDiffer.hpp"
#include "estrutura/nucleo/IVersionHistory.hpp"
#include "estrutura/nucleo/IVersionStore.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/Version.hpp"

namespace estrutura::nucleo {
class VersionHistory : public IVersionHistory {

	IVersionStore& store;

	const IDiffer& differ;

	const IClock& clock;

	[[nodiscard]] Version find(const std::string& document, int versionNumber) const;

public:
	VersionHistory(IVersionStore& store, const IDiffer& differ, const IClock& clock);

	std::optional<Version> save(const std::string& document, const std::string& text, const std::string& message) override;

	[[nodiscard]] std::vector<Version> versions(const std::string& document) const override;

	[[nodiscard]] TextDiff diff(const std::string& document, int fromVersion, int toVersion) const override;

	[[nodiscard]] TextDiff changesSinceLatest(const std::string& document, const std::string& text) const override;

	std::optional<Version> restore(const std::string& document, int versionNumber) override;

	[[nodiscard]] std::vector<std::string> documents() const override;

};

}  // namespace estrutura::nucleo
#endif
