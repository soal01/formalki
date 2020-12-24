project(Testing)


add_executable(TestExe main_test.cpp tests.cpp)

target_link_libraries(TestExe gtest_main Algo_lib)
target_include_directories(TestExe PRIVATE ${Practice2_SOURCE_DIR})