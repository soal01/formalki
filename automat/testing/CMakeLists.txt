project(Testing)


add_executable(TestExe main_test.cpp tests.cpp)

target_link_libraries(TestExe gtest_main automat_lib)
target_include_directories(TestExe PRIVATE ${Automat_SOURCE_DIR})