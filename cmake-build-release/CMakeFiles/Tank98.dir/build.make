# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /mnt/d/NetworkProgramming/Tank98

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/NetworkProgramming/Tank98/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/Tank98.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Tank98.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Tank98.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tank98.dir/flags.make

CMakeFiles/Tank98.dir/main.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/main.cpp.o: /mnt/d/NetworkProgramming/Tank98/main.cpp
CMakeFiles/Tank98.dir/main.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/NetworkProgramming/Tank98/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tank98.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/main.cpp.o -MF CMakeFiles/Tank98.dir/main.cpp.o.d -o CMakeFiles/Tank98.dir/main.cpp.o -c /mnt/d/NetworkProgramming/Tank98/main.cpp

CMakeFiles/Tank98.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/NetworkProgramming/Tank98/main.cpp > CMakeFiles/Tank98.dir/main.cpp.i

CMakeFiles/Tank98.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/NetworkProgramming/Tank98/main.cpp -o CMakeFiles/Tank98.dir/main.cpp.s

CMakeFiles/Tank98.dir/math.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/math.cpp.o: /mnt/d/NetworkProgramming/Tank98/math.cpp
CMakeFiles/Tank98.dir/math.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/NetworkProgramming/Tank98/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Tank98.dir/math.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/math.cpp.o -MF CMakeFiles/Tank98.dir/math.cpp.o.d -o CMakeFiles/Tank98.dir/math.cpp.o -c /mnt/d/NetworkProgramming/Tank98/math.cpp

CMakeFiles/Tank98.dir/math.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/math.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/NetworkProgramming/Tank98/math.cpp > CMakeFiles/Tank98.dir/math.cpp.i

CMakeFiles/Tank98.dir/math.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/math.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/NetworkProgramming/Tank98/math.cpp -o CMakeFiles/Tank98.dir/math.cpp.s

# Object files for target Tank98
Tank98_OBJECTS = \
"CMakeFiles/Tank98.dir/main.cpp.o" \
"CMakeFiles/Tank98.dir/math.cpp.o"

# External object files for target Tank98
Tank98_EXTERNAL_OBJECTS =

Tank98: CMakeFiles/Tank98.dir/main.cpp.o
Tank98: CMakeFiles/Tank98.dir/math.cpp.o
Tank98: CMakeFiles/Tank98.dir/build.make
Tank98: /usr/lib/x86_64-linux-gnu/libSDL2.so
Tank98: CMakeFiles/Tank98.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/d/NetworkProgramming/Tank98/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Tank98"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tank98.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tank98.dir/build: Tank98
.PHONY : CMakeFiles/Tank98.dir/build

CMakeFiles/Tank98.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tank98.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tank98.dir/clean

CMakeFiles/Tank98.dir/depend:
	cd /mnt/d/NetworkProgramming/Tank98/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/NetworkProgramming/Tank98 /mnt/d/NetworkProgramming/Tank98 /mnt/d/NetworkProgramming/Tank98/cmake-build-release /mnt/d/NetworkProgramming/Tank98/cmake-build-release /mnt/d/NetworkProgramming/Tank98/cmake-build-release/CMakeFiles/Tank98.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Tank98.dir/depend

