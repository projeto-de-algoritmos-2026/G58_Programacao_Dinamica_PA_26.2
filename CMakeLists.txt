cmake_minimum_required(VERSION 3.20)
project(programacao_dinamica_g58 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(version_core STATIC
        estrutura/alinhamento/AlignmentColumn.cpp
        estrutura/alinhamento/CostTable.cpp
        estrutura/alinhamento/NeedlemanWunschAligner.cpp
        estrutura/nucleo/AlignmentDiffer.cpp
        estrutura/nucleo/DiffAssembler.cpp
        estrutura/nucleo/TextDiff.cpp
        estrutura/nucleo/TextSplitter.cpp
        estrutura/nucleo/TokenAlignmentProblem.cpp
        estrutura/terminal/TerminalUI.cpp

        estrutura/adaptadores/FolderVersionStore.cpp
        estrutura/adaptadores/SystemClock.cpp
        estrutura/alinhamento/HirschbergAligner.cpp
        estrutura/alinhamento/IndexRange.cpp
        estrutura/alinhamento/LinearSpaceCost.cpp
        estrutura/alinhamento/LongestIncreasingSubsequence.cpp
        estrutura/alinhamento/SubProblem.cpp
        estrutura/nucleo/PatienceDiffer.cpp
        estrutura/nucleo/VersionHistory.cpp
)

target_include_directories(version_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(version_core PRIVATE -Wall -Wextra)
endif ()

add_executable(version estrutura/terminal/main.cpp)
target_link_libraries(version PRIVATE version_core)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bench/bench_diff.cpp)
    add_executable(version_bench bench/bench_diff.cpp)
    target_link_libraries(version_bench PRIVATE version_core)
endif ()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
    enable_testing()
    add_subdirectory(tests)
endif ()
