# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\github\skiplist

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\github\skiplist\build

# Utility rule file for NightlyTest.

# Include the progress variables for this target.
include tests/CMakeFiles/NightlyTest.dir/progress.make

tests/CMakeFiles/NightlyTest:
	cd /d C:\github\skiplist\build\tests && "C:\Program Files\CMake\bin\ctest.exe" -D NightlyTest

NightlyTest: tests/CMakeFiles/NightlyTest
NightlyTest: tests/CMakeFiles/NightlyTest.dir/build.make

.PHONY : NightlyTest

# Rule to build all files generated by this target.
tests/CMakeFiles/NightlyTest.dir/build: NightlyTest

.PHONY : tests/CMakeFiles/NightlyTest.dir/build

tests/CMakeFiles/NightlyTest.dir/clean:
	cd /d C:\github\skiplist\build\tests && $(CMAKE_COMMAND) -P CMakeFiles\NightlyTest.dir\cmake_clean.cmake
.PHONY : tests/CMakeFiles/NightlyTest.dir/clean

tests/CMakeFiles/NightlyTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\github\skiplist C:\github\skiplist\tests C:\github\skiplist\build C:\github\skiplist\build\tests C:\github\skiplist\build\tests\CMakeFiles\NightlyTest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/NightlyTest.dir/depend
