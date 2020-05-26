
add_executable(
  invocation_binder_test
  invocation_binder_test.cpp
)

add_test(
  NAME invocation_binder_test
  COMMAND $<TARGET_FILE:invocation_binder_test> --success
)
