# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = C:\Ohjelmointi\AudioEQ\libs\aquila

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Ohjelmointi\AudioEQ\libs\aquila\build

# Utility rule file for check.

# Include any custom commands dependencies for this target.
include lib/unittestpp/CMakeFiles/check.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/unittestpp/CMakeFiles/check.dir/progress.make

lib/unittestpp/CMakeFiles/check:
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\lib\unittestpp && "C:\Program Files\CMake\bin\ctest.exe" -V

check: lib/unittestpp/CMakeFiles/check
check: lib/unittestpp/CMakeFiles/check.dir/build.make
.PHONY : check

# Rule to build all files generated by this target.
lib/unittestpp/CMakeFiles/check.dir/build: check
.PHONY : lib/unittestpp/CMakeFiles/check.dir/build

lib/unittestpp/CMakeFiles/check.dir/clean:
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\lib\unittestpp && $(CMAKE_COMMAND) -P CMakeFiles\check.dir\cmake_clean.cmake
.PHONY : lib/unittestpp/CMakeFiles/check.dir/clean

lib/unittestpp/CMakeFiles/check.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Ohjelmointi\AudioEQ\libs\aquila C:\Ohjelmointi\AudioEQ\libs\aquila\lib\unittestpp C:\Ohjelmointi\AudioEQ\libs\aquila\build C:\Ohjelmointi\AudioEQ\libs\aquila\build\lib\unittestpp C:\Ohjelmointi\AudioEQ\libs\aquila\build\lib\unittestpp\CMakeFiles\check.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : lib/unittestpp/CMakeFiles/check.dir/depend

