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

# Include any dependencies generated for this target.
include examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/progress.make

# Include the compile flags for this target's objects.
include examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/flags.make

examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/flags.make
examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/includes_CXX.rsp
examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj: ../examples/mfcc_calculation/mfcc_calculation.cpp
examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\mfcc_calculation && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj -MF CMakeFiles\mfcc_calculation.dir\mfcc_calculation.cpp.obj.d -o CMakeFiles\mfcc_calculation.dir\mfcc_calculation.cpp.obj -c C:\Ohjelmointi\AudioEQ\libs\aquila\examples\mfcc_calculation\mfcc_calculation.cpp

examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.i"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\mfcc_calculation && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Ohjelmointi\AudioEQ\libs\aquila\examples\mfcc_calculation\mfcc_calculation.cpp > CMakeFiles\mfcc_calculation.dir\mfcc_calculation.cpp.i

examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.s"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\mfcc_calculation && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Ohjelmointi\AudioEQ\libs\aquila\examples\mfcc_calculation\mfcc_calculation.cpp -o CMakeFiles\mfcc_calculation.dir\mfcc_calculation.cpp.s

# Object files for target mfcc_calculation
mfcc_calculation_OBJECTS = \
"CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj"

# External object files for target mfcc_calculation
mfcc_calculation_EXTERNAL_OBJECTS =

examples/mfcc_calculation/mfcc_calculation.exe: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/mfcc_calculation.cpp.obj
examples/mfcc_calculation/mfcc_calculation.exe: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/build.make
examples/mfcc_calculation/mfcc_calculation.exe: libAquila.a
examples/mfcc_calculation/mfcc_calculation.exe: lib/libOoura_fft.a
examples/mfcc_calculation/mfcc_calculation.exe: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/linklibs.rsp
examples/mfcc_calculation/mfcc_calculation.exe: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/objects1.rsp
examples/mfcc_calculation/mfcc_calculation.exe: examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mfcc_calculation.exe"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\mfcc_calculation && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mfcc_calculation.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/build: examples/mfcc_calculation/mfcc_calculation.exe
.PHONY : examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/build

examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/clean:
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\mfcc_calculation && $(CMAKE_COMMAND) -P CMakeFiles\mfcc_calculation.dir\cmake_clean.cmake
.PHONY : examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/clean

examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Ohjelmointi\AudioEQ\libs\aquila C:\Ohjelmointi\AudioEQ\libs\aquila\examples\mfcc_calculation C:\Ohjelmointi\AudioEQ\libs\aquila\build C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\mfcc_calculation C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\mfcc_calculation\CMakeFiles\mfcc_calculation.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/mfcc_calculation/CMakeFiles/mfcc_calculation.dir/depend

