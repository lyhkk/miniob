add_test([=[IntegerGenerator.test]=]  /home/lyhkk/miniob/bin/integer_generator_test [==[--gtest_filter=IntegerGenerator.test]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IntegerGenerator.test]=]  PROPERTIES WORKING_DIRECTORY /home/lyhkk/miniob/unittest SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  integer_generator_test_TESTS IntegerGenerator.test)
