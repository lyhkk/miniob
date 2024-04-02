# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lyhkk/miniob

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lyhkk/miniob

# Include any dependencies generated for this target.
include unittest/CMakeFiles/pidfile_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include unittest/CMakeFiles/pidfile_test.dir/compiler_depend.make

# Include the progress variables for this target.
include unittest/CMakeFiles/pidfile_test.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/CMakeFiles/pidfile_test.dir/flags.make

unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o: unittest/CMakeFiles/pidfile_test.dir/flags.make
unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o: unittest/pidfile_test.cpp
unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o: unittest/CMakeFiles/pidfile_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lyhkk/miniob/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o"
	cd /home/lyhkk/miniob/unittest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o -MF CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o.d -o CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o -c /home/lyhkk/miniob/unittest/pidfile_test.cpp

unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pidfile_test.dir/pidfile_test.cpp.i"
	cd /home/lyhkk/miniob/unittest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lyhkk/miniob/unittest/pidfile_test.cpp > CMakeFiles/pidfile_test.dir/pidfile_test.cpp.i

unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pidfile_test.dir/pidfile_test.cpp.s"
	cd /home/lyhkk/miniob/unittest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lyhkk/miniob/unittest/pidfile_test.cpp -o CMakeFiles/pidfile_test.dir/pidfile_test.cpp.s

# Object files for target pidfile_test
pidfile_test_OBJECTS = \
"CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o"

# External object files for target pidfile_test
pidfile_test_EXTERNAL_OBJECTS =

bin/pidfile_test: unittest/CMakeFiles/pidfile_test.dir/pidfile_test.cpp.o
bin/pidfile_test: unittest/CMakeFiles/pidfile_test.dir/build.make
bin/pidfile_test: lib/libcommon.a
bin/pidfile_test: lib/libobserver.a
bin/pidfile_test: lib/libcommon.a
bin/pidfile_test: /usr/lib/x86_64-linux-gnu/libreadline.so
bin/pidfile_test: /home/lyhkk/anaconda3/lib/libevent_pthreads.a
bin/pidfile_test: /home/lyhkk/anaconda3/lib/libevent_core.a
bin/pidfile_test: unittest/CMakeFiles/pidfile_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lyhkk/miniob/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/pidfile_test"
	cd /home/lyhkk/miniob/unittest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pidfile_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/lyhkk/miniob/unittest && /usr/local/bin/cmake -D TEST_TARGET=pidfile_test -D TEST_EXECUTABLE=/home/lyhkk/miniob/bin/pidfile_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/lyhkk/miniob/unittest -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=pidfile_test_TESTS -D CTEST_FILE=/home/lyhkk/miniob/unittest/pidfile_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/local/share/cmake-3.26/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
unittest/CMakeFiles/pidfile_test.dir/build: bin/pidfile_test
.PHONY : unittest/CMakeFiles/pidfile_test.dir/build

unittest/CMakeFiles/pidfile_test.dir/clean:
	cd /home/lyhkk/miniob/unittest && $(CMAKE_COMMAND) -P CMakeFiles/pidfile_test.dir/cmake_clean.cmake
.PHONY : unittest/CMakeFiles/pidfile_test.dir/clean

unittest/CMakeFiles/pidfile_test.dir/depend:
	cd /home/lyhkk/miniob && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lyhkk/miniob /home/lyhkk/miniob/unittest /home/lyhkk/miniob /home/lyhkk/miniob/unittest /home/lyhkk/miniob/unittest/CMakeFiles/pidfile_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/CMakeFiles/pidfile_test.dir/depend

