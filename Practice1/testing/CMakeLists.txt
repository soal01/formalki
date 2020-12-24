project(Testing)


add_executable(TestExe main_test.cpp tests.cpp)

target_link_libraries(TestExe gtest_main reg_lib)
target_include_directories(TestExe PRIVATE ${Practice1_SOURCE_DIR})