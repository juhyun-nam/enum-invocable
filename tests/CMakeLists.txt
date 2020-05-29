add_executable(invocation_binder_test invocation_binder_test.cc)

target_compile_options(invocation_binder_test PRIVATE -O0 -g --coverage)

add_library(doctest INTERFACE)

target_include_directories(doctest
                           INTERFACE ${PROJECT_SOURCE_DIR}/external/doctest)

target_link_libraries(invocation_binder_test PRIVATE doctest --coverage)

add_test(NAME invocation_binder_test
         COMMAND $<TARGET_FILE:invocation_binder_test> --success)
