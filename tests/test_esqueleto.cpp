#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

#include "Mocks.hpp"

#include "estrutura/alinhamento/Alignment.hpp"
#include "estrutura/alinhamento/NeedlemanWunschAligner.hpp"
#include "estrutura/nucleo/AlignmentDiffer.hpp"
#include "estrutura/nucleo/VersionHistory.hpp"
#include "estrutura/terminal/TerminalUI.hpp"

using estrutura::alinhamento::Alignment;
using estrutura::alinhamento::NeedlemanWunschAligner;
using estrutura::nucleo::AlignmentDiffer;
using estrutura::nucleo::VersionHistory;
using estrutura::terminal::TerminalUI;

using testing::Return;

TEST(Esqueleto, AlinhamentoNovoComecaComCustoZero) {
	const Alignment alignment{};

	EXPECT_EQ(alignment.cost, 0);
	EXPECT_TRUE(alignment.columns.empty());
}

TEST(Esqueleto, AsClassesDaEntregaSeMontamComoNoMain) {
	const NeedlemanWunschAligner aligner;
	const AlignmentDiffer differ(aligner);
	const TerminalUI terminal(differ, std::cin, std::cout);

	SUCCEED();
}

TEST(Esqueleto, OHistoricoSeMontaComMocks) {
	mocks::MockVersionStore store;
	mocks::MockDiffer differ;
	mocks::MockClock clock;

	VersionHistory history(store, differ, clock);

	SUCCEED();
}

TEST(Esqueleto, UmMockDevolveOQueOTesteManda) {
	mocks::MockClock clock;
	EXPECT_CALL(clock, now()).WillOnce(Return("2026-11-18 11:24"));

	EXPECT_EQ(clock.now(), "2026-11-18 11:24");
}
