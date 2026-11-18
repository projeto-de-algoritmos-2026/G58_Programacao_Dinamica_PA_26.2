#ifndef TESTS_MOCKS_H
#define TESTS_MOCKS_H

#include <optional>
#include <string>
#include <vector>

#include <gmock/gmock.h>

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/IAligner.hpp"
#include "estrutura/alinhamento/IAlignmentProblem.hpp"
#include "estrutura/nucleo/IClock.hpp"
#include "estrutura/nucleo/IDiffer.hpp"
#include "estrutura/nucleo/IVersionHistory.hpp"
#include "estrutura/nucleo/IVersionStore.hpp"
#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/Version.hpp"

namespace mocks {

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::IAligner;
using estrutura::alinhamento::IAlignmentProblem;
using estrutura::nucleo::IClock;
using estrutura::nucleo::IDiffer;
using estrutura::nucleo::IVersionHistory;
using estrutura::nucleo::IVersionStore;
using estrutura::nucleo::TextDiff;
using estrutura::nucleo::Version;

class MockAlignmentProblem : public IAlignmentProblem {
public:
	MOCK_METHOD(int, lengthX, (), (const, override));
	MOCK_METHOD(int, lengthY, (), (const, override));
	MOCK_METHOD(int, pairCost, (int xIndex, int yIndex), (const, override));
	MOCK_METHOD(int, unmatchedXCost, (int xIndex), (const, override));
	MOCK_METHOD(int, unmatchedYCost, (int yIndex), (const, override));
};

class MockAligner : public IAligner {
public:
	MOCK_METHOD(Alignment, align, (const IAlignmentProblem& problem), (const, override));
};

class MockDiffer : public IDiffer {
public:
	MOCK_METHOD(TextDiff, diff, (const std::string& before, const std::string& after), (const, override));
};

class MockClock : public IClock {
public:
	MOCK_METHOD(std::string, now, (), (const, override));
};

class MockVersionStore : public IVersionStore {
public:
	MOCK_METHOD(void, append, (const std::string& document, const Version& version), (override));
	MOCK_METHOD(std::vector<Version>, versions, (const std::string& document), (const, override));
	MOCK_METHOD(std::vector<std::string>, documents, (), (const, override));
};

class MockVersionHistory : public IVersionHistory {
public:
	MOCK_METHOD(std::optional<Version>, save, (const std::string& document, const std::string& text, const std::string& message), (override));
	MOCK_METHOD(std::vector<Version>, versions, (const std::string& document), (const, override));
	MOCK_METHOD(TextDiff, diff, (const std::string& document, int fromVersion, int toVersion), (const, override));
	MOCK_METHOD(TextDiff, changesSinceLatest, (const std::string& document, const std::string& text), (const, override));
	MOCK_METHOD(std::optional<Version>, restore, (const std::string& document, int versionNumber), (override));
	MOCK_METHOD(std::vector<std::string>, documents, (), (const, override));
};

}  // namespace mocks
#endif
