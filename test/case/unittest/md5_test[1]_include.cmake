if(EXISTS "/root/miniob/test/case/unittest/md5_test[1]_tests.cmake")
  include("/root/miniob/test/case/unittest/md5_test[1]_tests.cmake")
else()
  add_test(md5_test_NOT_BUILT md5_test_NOT_BUILT)
endif()
