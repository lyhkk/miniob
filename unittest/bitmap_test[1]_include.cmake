if(EXISTS "/home/lyhkk/miniob/unittest/bitmap_test[1]_tests.cmake")
  include("/home/lyhkk/miniob/unittest/bitmap_test[1]_tests.cmake")
else()
  add_test(bitmap_test_NOT_BUILT bitmap_test_NOT_BUILT)
endif()
