# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cpp_fall2022/project05

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cpp_fall2022/project05/build

# Include any dependencies generated for this target.
include bin/CMakeFiles/matrixClassTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include bin/CMakeFiles/matrixClassTest.dir/compiler_depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/matrixClassTest.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/matrixClassTest.dir/flags.make

bin/CMakeFiles/matrixClassTest.dir/test.o: bin/CMakeFiles/matrixClassTest.dir/flags.make
bin/CMakeFiles/matrixClassTest.dir/test.o: ../src/test.cpp
bin/CMakeFiles/matrixClassTest.dir/test.o: bin/CMakeFiles/matrixClassTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cpp_fall2022/project05/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/matrixClassTest.dir/test.o"
	cd /home/cpp_fall2022/project05/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bin/CMakeFiles/matrixClassTest.dir/test.o -MF CMakeFiles/matrixClassTest.dir/test.o.d -o CMakeFiles/matrixClassTest.dir/test.o -c /home/cpp_fall2022/project05/src/test.cpp

bin/CMakeFiles/matrixClassTest.dir/test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrixClassTest.dir/test.i"
	cd /home/cpp_fall2022/project05/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cpp_fall2022/project05/src/test.cpp > CMakeFiles/matrixClassTest.dir/test.i

bin/CMakeFiles/matrixClassTest.dir/test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrixClassTest.dir/test.s"
	cd /home/cpp_fall2022/project05/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cpp_fall2022/project05/src/test.cpp -o CMakeFiles/matrixClassTest.dir/test.s

# Object files for target matrixClassTest
matrixClassTest_OBJECTS = \
"CMakeFiles/matrixClassTest.dir/test.o"

# External object files for target matrixClassTest
matrixClassTest_EXTERNAL_OBJECTS =

bin/matrixClassTest: bin/CMakeFiles/matrixClassTest.dir/test.o
bin/matrixClassTest: bin/CMakeFiles/matrixClassTest.dir/build.make
bin/matrixClassTest: bin/CMakeFiles/matrixClassTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cpp_fall2022/project05/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable matrixClassTest"
	cd /home/cpp_fall2022/project05/build/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrixClassTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/matrixClassTest.dir/build: bin/matrixClassTest
.PHONY : bin/CMakeFiles/matrixClassTest.dir/build

bin/CMakeFiles/matrixClassTest.dir/clean:
	cd /home/cpp_fall2022/project05/build/bin && $(CMAKE_COMMAND) -P CMakeFiles/matrixClassTest.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/matrixClassTest.dir/clean

bin/CMakeFiles/matrixClassTest.dir/depend:
	cd /home/cpp_fall2022/project05/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cpp_fall2022/project05 /home/cpp_fall2022/project05/src /home/cpp_fall2022/project05/build /home/cpp_fall2022/project05/build/bin /home/cpp_fall2022/project05/build/bin/CMakeFiles/matrixClassTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/matrixClassTest.dir/depend

