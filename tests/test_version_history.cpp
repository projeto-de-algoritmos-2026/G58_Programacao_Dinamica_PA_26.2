#include <optional>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "Mocks.hpp"

#include "estrutura/nucleo/TextDiff.hpp"
#include "estrutura/nucleo/Version.hpp"
#include "estrutura/nucleo/VersionHistory.hpp"

using estrutura::nucleo::TextDiff;
using estrutura::nucleo::Version;
using estrutura::nucleo::VersionHistory;

using mocks::MockClock;
using mocks::MockDiffer;
using mocks::MockVersionStore;
using testing::_;
using testing::Return;