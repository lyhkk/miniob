add_test([=[checkRotateTest.CheckRoateTest]=]  /home/lyhkk/miniob/bin/log_test [==[--gtest_filter=checkRotateTest.CheckRoateTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[checkRotateTest.CheckRoateTest]=]  PROPERTIES WORKING_DIRECTORY /home/lyhkk/miniob/unittest SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[testEnableTest.CheckEnableTest]=]  /home/lyhkk/miniob/bin/log_test [==[--gtest_filter=testEnableTest.CheckEnableTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[testEnableTest.CheckEnableTest]=]  PROPERTIES WORKING_DIRECTORY /home/lyhkk/miniob/unittest SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  log_test_TESTS checkRotateTest.CheckRoateTest testEnableTest.CheckEnableTest)
