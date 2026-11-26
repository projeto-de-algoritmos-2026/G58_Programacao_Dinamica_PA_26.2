include(FetchContent)
FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(googletest)

add_executable(version_tests
        Mocks.hpp
        test_esqueleto.cpp
        test_structs.cpp
        test_cost_table.cpp
        test_needleman_wunsch.cpp
        test_oraculos.cpp
        test_text_splitter.cpp
        test_token_problem.cpp
        test_diff_assembler.cpp
        test_alignment_differ.cpp
        test_dados_reais.cpp

        test_linear_space_cost.cpp
        test_subproblem.cpp
        test_hirschberg.cpp
        test_lis.cpp
        test_patience_differ.cpp
        test_version_history.cpp
        test_folder_store.cpp

        StringProblem.hpp
        AlignmentOracle.hpp
        RandomProblem.hpp
        DiffOracle.hpp
        test_terminal_ui.cpp
)

target_compile_definitions(version_tests PRIVATE EXEMPLOS_DIR="${PROJECT_SOURCE_DIR}/exemplos")

target_link_libraries(version_tests PRIVATE version_core GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(version_tests)
