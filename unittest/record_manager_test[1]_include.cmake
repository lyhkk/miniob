if(EXISTS "/home/lyhkk/miniob/unittest/record_manager_test[1]_tests.cmake")
  include("/home/lyhkk/miniob/unittest/record_manager_test[1]_tests.cmake")
else()
  add_test(record_manager_test_NOT_BUILT record_manager_test_NOT_BUILT)
endif()
