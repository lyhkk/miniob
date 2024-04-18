add_test([=[test_bitmap.test_bitmap]=]  /home/lyhkk/miniob/bin/bitmap_test [==[--gtest_filter=test_bitmap.test_bitmap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[test_bitmap.test_bitmap]=]  PROPERTIES WORKING_DIRECTORY /home/lyhkk/miniob/unittest SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  bitmap_test_TESTS test_bitmap.test_bitmap)
