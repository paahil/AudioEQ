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
include examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/progress.make

# Include the compile flags for this target's objects.
include examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/flags.make

examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/flags.make
examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/includes_CXX.rsp
examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj: ../examples/dtw_path_recovery/dtw_path_recovery.cpp
examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\dtw_path_recovery && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj -MF CMakeFiles\dtw_path_recovery.dir\dtw_path_recovery.cpp.obj.d -o CMakeFiles\dtw_path_recovery.dir\dtw_path_recovery.cpp.obj -c C:\Ohjelmointi\AudioEQ\libs\aquila\examples\dtw_path_recovery\dtw_path_recovery.cpp

examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.i"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\dtw_path_recovery && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Ohjelmointi\AudioEQ\libs\aquila\examples\dtw_path_recovery\dtw_path_recovery.cpp > CMakeFiles\dtw_path_recovery.dir\dtw_path_recovery.cpp.i

examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.s"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\dtw_path_recovery && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Ohjelmointi\AudioEQ\libs\aquila\examples\dtw_path_recovery\dtw_path_recovery.cpp -o CMakeFiles\dtw_path_recovery.dir\dtw_path_recovery.cpp.s

# Object files for target dtw_path_recovery
dtw_path_recovery_OBJECTS = \
"CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj"

# External object files for target dtw_path_recovery
dtw_path_recovery_EXTERNAL_OBJECTS =

examples/dtw_path_recovery/dtw_path_recovery.exe: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/dtw_path_recovery.cpp.obj
examples/dtw_path_recovery/dtw_path_recovery.exe: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/build.make
examples/dtw_path_recovery/dtw_path_recovery.exe: libAquila.a
examples/dtw_path_recovery/dtw_path_recovery.exe: lib/libOoura_fft.a
examples/dtw_path_recovery/dtw_path_recovery.exe: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/linklibs.rsp
examples/dtw_path_recovery/dtw_path_recovery.exe: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/objects1.rsp
examples/dtw_path_recovery/dtw_path_recovery.exe: examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dtw_path_recovery.exe"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\dtw_path_recovery && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\dtw_path_recovery.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/build: examples/dtw_path_recovery/dtw_path_recovery.exe
.PHONY : examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/build

examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/clean:
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\dtw_path_recovery && $(CMAKE_COMMAND) -P CMakeFiles\dtw_path_recovery.dir\cmake_clean.cmake
.PHONY : examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/clean

examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Ohjelmointi\AudioEQ\libs\aquila C:\Ohjelmointi\AudioEQ\libs\aquila\examples\dtw_path_recovery C:\Ohjelmointi\AudioEQ\libs\aquila\build C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\dtw_path_recovery C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\dtw_path_recovery\CMakeFiles\dtw_path_recovery.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/dtw_path_recovery/CMakeFiles/dtw_path_recovery.dir/depend
