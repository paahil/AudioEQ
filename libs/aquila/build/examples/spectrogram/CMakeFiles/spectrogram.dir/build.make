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
include examples/spectrogram/CMakeFiles/spectrogram.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/spectrogram/CMakeFiles/spectrogram.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/spectrogram/CMakeFiles/spectrogram.dir/progress.make

# Include the compile flags for this target's objects.
include examples/spectrogram/CMakeFiles/spectrogram.dir/flags.make

examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.obj: examples/spectrogram/CMakeFiles/spectrogram.dir/flags.make
examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.obj: examples/spectrogram/CMakeFiles/spectrogram.dir/includes_CXX.rsp
examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.obj: ../examples/spectrogram/spectrogram.cpp
examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.obj: examples/spectrogram/CMakeFiles/spectrogram.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.obj"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\spectrogram && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.obj -MF CMakeFiles\spectrogram.dir\spectrogram.cpp.obj.d -o CMakeFiles\spectrogram.dir\spectrogram.cpp.obj -c C:\Ohjelmointi\AudioEQ\libs\aquila\examples\spectrogram\spectrogram.cpp

examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spectrogram.dir/spectrogram.cpp.i"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\spectrogram && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Ohjelmointi\AudioEQ\libs\aquila\examples\spectrogram\spectrogram.cpp > CMakeFiles\spectrogram.dir\spectrogram.cpp.i

examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spectrogram.dir/spectrogram.cpp.s"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\spectrogram && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Ohjelmointi\AudioEQ\libs\aquila\examples\spectrogram\spectrogram.cpp -o CMakeFiles\spectrogram.dir\spectrogram.cpp.s

# Object files for target spectrogram
spectrogram_OBJECTS = \
"CMakeFiles/spectrogram.dir/spectrogram.cpp.obj"

# External object files for target spectrogram
spectrogram_EXTERNAL_OBJECTS =

examples/spectrogram/spectrogram.exe: examples/spectrogram/CMakeFiles/spectrogram.dir/spectrogram.cpp.obj
examples/spectrogram/spectrogram.exe: examples/spectrogram/CMakeFiles/spectrogram.dir/build.make
examples/spectrogram/spectrogram.exe: libAquila.a
examples/spectrogram/spectrogram.exe: lib/libOoura_fft.a
examples/spectrogram/spectrogram.exe: examples/spectrogram/CMakeFiles/spectrogram.dir/linklibs.rsp
examples/spectrogram/spectrogram.exe: examples/spectrogram/CMakeFiles/spectrogram.dir/objects1.rsp
examples/spectrogram/spectrogram.exe: examples/spectrogram/CMakeFiles/spectrogram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Ohjelmointi\AudioEQ\libs\aquila\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable spectrogram.exe"
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\spectrogram && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\spectrogram.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/spectrogram/CMakeFiles/spectrogram.dir/build: examples/spectrogram/spectrogram.exe
.PHONY : examples/spectrogram/CMakeFiles/spectrogram.dir/build

examples/spectrogram/CMakeFiles/spectrogram.dir/clean:
	cd /d C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\spectrogram && $(CMAKE_COMMAND) -P CMakeFiles\spectrogram.dir\cmake_clean.cmake
.PHONY : examples/spectrogram/CMakeFiles/spectrogram.dir/clean

examples/spectrogram/CMakeFiles/spectrogram.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Ohjelmointi\AudioEQ\libs\aquila C:\Ohjelmointi\AudioEQ\libs\aquila\examples\spectrogram C:\Ohjelmointi\AudioEQ\libs\aquila\build C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\spectrogram C:\Ohjelmointi\AudioEQ\libs\aquila\build\examples\spectrogram\CMakeFiles\spectrogram.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/spectrogram/CMakeFiles/spectrogram.dir/depend
