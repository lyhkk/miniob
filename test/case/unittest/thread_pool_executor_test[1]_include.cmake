if(EXISTS "/root/miniob/test/case/unittest/thread_pool_executor_test[1]_tests.cmake")
  include("/root/miniob/test/case/unittest/thread_pool_executor_test[1]_tests.cmake")
else()
  add_test(thread_pool_executor_test_NOT_BUILT thread_pool_executor_test_NOT_BUILT)
endif()
