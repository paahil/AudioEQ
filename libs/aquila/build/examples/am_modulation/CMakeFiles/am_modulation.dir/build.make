# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = C:\Users\Paavo\Documents\AudioEQ\libs\aquila

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build

# Include any dependencies generated for this target.
include examples/am_modulation/CMakeFiles/am_modulation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/am_modulation/CMakeFiles/am_modulation.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/am_modulation/CMakeFiles/am_modulation.dir/progress.make

# Include the compile flags for this target's objects.
include examples/am_modulation/CMakeFiles/am_modulation.dir/flags.make

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.obj: examples/am_modulation/CMakeFiles/am_modulation.dir/flags.make
examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.obj: examples/am_modulation/CMakeFiles/am_modulation.dir/includes_CXX.rsp
examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.obj: ../examples/am_modulation/am_modulation.cpp
examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.obj: examples/am_modulation/CMakeFiles/am_modulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.obj"
	cd /d C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\examples\am_modulation && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.obj -MF CMakeFiles\am_modulation.dir\am_modulation.cpp.obj.d -o CMakeFiles\am_modulation.dir\am_modulation.cpp.obj -c C:\Users\Paavo\Documents\AudioEQ\libs\aquila\examples\am_modulation\am_modulation.cpp

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/am_modulation.dir/am_modulation.cpp.i"
	cd /d C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\examples\am_modulation && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Paavo\Documents\AudioEQ\libs\aquila\examples\am_modulation\am_modulation.cpp > CMakeFiles\am_modulation.dir\am_modulation.cpp.i

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/am_modulation.dir/am_modulation.cpp.s"
	cd /d C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\examples\am_modulation && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Paavo\Documents\AudioEQ\libs\aquila\examples\am_modulation\am_modulation.cpp -o CMakeFiles\am_modulation.dir\am_modulation.cpp.s

# Object files for target am_modulation
am_modulation_OBJECTS = \
"CMakeFiles/am_modulation.dir/am_modulation.cpp.obj"

# External object files for target am_modulation
am_modulation_EXTERNAL_OBJECTS =

examples/am_modulation/am_modulation.exe: examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.obj
examples/am_modulation/am_modulation.exe: examples/am_modulation/CMakeFiles/am_modulation.dir/build.make
examples/am_modulation/am_modulation.exe: libAquila.a
examples/am_modulation/am_modulation.exe: lib/libOoura_fft.a
examples/am_modulation/am_modulation.exe: examples/am_modulation/CMakeFiles/am_modulation.dir/linklibs.rsp
examples/am_modulation/am_modulation.exe: examples/am_modulation/CMakeFiles/am_modulation.dir/objects1.rsp
examples/am_modulation/am_modulation.exe: examples/am_modulation/CMakeFiles/am_modulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable am_modulation.exe"
	cd /d C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\examples\am_modulation && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\am_modulation.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/am_modulation/CMakeFiles/am_modulation.dir/build: examples/am_modulation/am_modulation.exe
.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/build

examples/am_modulation/CMakeFiles/am_modulation.dir/clean:
	cd /d C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\examples\am_modulation && $(CMAKE_COMMAND) -P CMakeFiles\am_modulation.dir\cmake_clean.cmake
.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/clean

examples/am_modulation/CMakeFiles/am_modulation.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Paavo\Documents\AudioEQ\libs\aquila C:\Users\Paavo\Documents\AudioEQ\libs\aquila\examples\am_modulation C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\examples\am_modulation C:\Users\Paavo\Documents\AudioEQ\libs\aquila\build\examples\am_modulation\CMakeFiles\am_modulation.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/depend

