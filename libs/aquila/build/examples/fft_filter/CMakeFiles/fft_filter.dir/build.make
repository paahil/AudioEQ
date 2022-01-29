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
include examples/fft_filter/CMakeFiles/fft_filter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/fft_filter/CMakeFiles/fft_filter.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/fft_filter/CMakeFiles/fft_filter.dir/progress.make

# Include the compile flags for this target's objects.
include examples/fft_filter/CMakeFiles/fft_filter.dir/flags.make

examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.obj: examples/fft_filter/CMakeFiles/fft_filter.dir/flags.make
examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.obj: examples/fft_filter/CMakeFiles/fft_filter.dir/includes_CXX.rsp
examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.obj: ../examples/fft_filter/fft_filter.cpp
examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.obj: examples/fft_filter/CMakeFiles/fft_filter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.obj"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\fft_filter && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.obj -MF CMakeFiles\fft_filter.dir\fft_filter.cpp.obj.d -o CMakeFiles\fft_filter.dir\fft_filter.cpp.obj -c C:\Ohjelmointi\AudioEQ\libs\aquila\examples\fft_filter\fft_filter.cpp

examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fft_filter.dir/fft_filter.cpp.i"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\fft_filter && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Ohjelmointi\AudioEQ\libs\aquila\examples\fft_filter\fft_filter.cpp > CMakeFiles\fft_filter.dir\fft_filter.cpp.i

examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fft_filter.dir/fft_filter.cpp.s"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\fft_filter && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Ohjelmointi\AudioEQ\libs\aquila\examples\fft_filter\fft_filter.cpp -o CMakeFiles\fft_filter.dir\fft_filter.cpp.s

# Object files for target fft_filter
fft_filter_OBJECTS = \
"CMakeFiles/fft_filter.dir/fft_filter.cpp.obj"

# External object files for target fft_filter
fft_filter_EXTERNAL_OBJECTS =

examples/fft_filter/fft_filter.exe: examples/fft_filter/CMakeFiles/fft_filter.dir/fft_filter.cpp.obj
examples/fft_filter/fft_filter.exe: examples/fft_filter/CMakeFiles/fft_filter.dir/build.make
examples/fft_filter/fft_filter.exe: libAquila.a
examples/fft_filter/fft_filter.exe: lib/libOoura_fft.a
examples/fft_filter/fft_filter.exe: examples/fft_filter/CMakeFiles/fft_filter.dir/linklibs.rsp
examples/fft_filter/fft_filter.exe: examples/fft_filter/CMakeFiles/fft_filter.dir/objects1.rsp
examples/fft_filter/fft_filter.exe: examples/fft_filter/CMakeFiles/fft_filter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fft_filter.exe"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\fft_filter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\fft_filter.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/fft_filter/CMakeFiles/fft_filter.dir/build: examples/fft_filter/fft_filter.exe
.PHONY : examples/fft_filter/CMakeFiles/fft_filter.dir/build

examples/fft_filter/CMakeFiles/fft_filter.dir/clean:
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\fft_filter && $(CMAKE_COMMAND) -P CMakeFiles\fft_filter.dir\cmake_clean.cmake
.PHONY : examples/fft_filter/CMakeFiles/fft_filter.dir/clean

examples/fft_filter/CMakeFiles/fft_filter.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Ohjelmointi\AudioEQ\libs\aquila C:\Ohjelmointi\AudioEQ\libs\aquila\examples\fft_filter C:\Ohjelmointi\AudioEQ\libs\aquila\build C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\fft_filter C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\fft_filter\CMakeFiles\fft_filter.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/fft_filter/CMakeFiles/fft_filter.dir/depend

