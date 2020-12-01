include(FetchContent)

FetchContent_Declare(
  extern_nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.1.0
  GIT_SHALLOW TRUE
)
# After the following call, the library will be installed
FetchContent_MakeAvailable(extern_nanobench)
FetchContent_MakeAvailable(extern_doctest)

# Google Benchmark needs threads!
find_package(Threads REQUIRED)

add_executable(run-bench ${CMAKE_CURRENT_SOURCE_DIR}/run-bench.cpp ${CMAKE_CURRENT_SOURCE_DIR}/bench-lib.cpp)
target_include_directories(run-bench PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty)
target_link_libraries(run-bench PRIVATE SimplifyLine::SPL doctest::doctest nanobench Threads::Threads)
