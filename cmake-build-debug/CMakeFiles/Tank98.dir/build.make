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
CMAKE_SOURCE_DIR = /mnt/d/Game/tank90-FE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Game/tank90-FE/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Tank98.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Tank98.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Tank98.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tank98.dir/flags.make

CMakeFiles/Tank98.dir/Source/main.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/Source/main.cpp.o: ../Source/main.cpp
CMakeFiles/Tank98.dir/Source/main.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tank98.dir/Source/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/Source/main.cpp.o -MF CMakeFiles/Tank98.dir/Source/main.cpp.o.d -o CMakeFiles/Tank98.dir/Source/main.cpp.o -c /mnt/d/Game/tank90-FE/Source/main.cpp

CMakeFiles/Tank98.dir/Source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/Source/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Game/tank90-FE/Source/main.cpp > CMakeFiles/Tank98.dir/Source/main.cpp.i

CMakeFiles/Tank98.dir/Source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/Source/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Game/tank90-FE/Source/main.cpp -o CMakeFiles/Tank98.dir/Source/main.cpp.s

CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o: ../Source/Math/Vector2.cpp
CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o -MF CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o.d -o CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o -c /mnt/d/Game/tank90-FE/Source/Math/Vector2.cpp

CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Game/tank90-FE/Source/Math/Vector2.cpp > CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.i

CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Game/tank90-FE/Source/Math/Vector2.cpp -o CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.s

CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o: ../Source/ECS/Component/Component.cpp
CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o -MF CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o.d -o CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o -c /mnt/d/Game/tank90-FE/Source/ECS/Component/Component.cpp

CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Game/tank90-FE/Source/ECS/Component/Component.cpp > CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.i

CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Game/tank90-FE/Source/ECS/Component/Component.cpp -o CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.s

CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o: ../Source/ECS/Entity/Entity.cpp
CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o -MF CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o.d -o CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o -c /mnt/d/Game/tank90-FE/Source/ECS/Entity/Entity.cpp

CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Game/tank90-FE/Source/ECS/Entity/Entity.cpp > CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.i

CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Game/tank90-FE/Source/ECS/Entity/Entity.cpp -o CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.s

CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o: ../Source/ECS/Entity/EntityManager.cpp
CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o -MF CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o.d -o CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o -c /mnt/d/Game/tank90-FE/Source/ECS/Entity/EntityManager.cpp

CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Game/tank90-FE/Source/ECS/Entity/EntityManager.cpp > CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.i

CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Game/tank90-FE/Source/ECS/Entity/EntityManager.cpp -o CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.s

CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o: ../Source/ECS/System/System.cpp
CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o -MF CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o.d -o CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o -c /mnt/d/Game/tank90-FE/Source/ECS/System/System.cpp

CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Game/tank90-FE/Source/ECS/System/System.cpp > CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.i

CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Game/tank90-FE/Source/ECS/System/System.cpp -o CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.s

CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o: CMakeFiles/Tank98.dir/flags.make
CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o: ../Source/ECS/System/SystemManager.cpp
CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o: CMakeFiles/Tank98.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o -MF CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o.d -o CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o -c /mnt/d/Game/tank90-FE/Source/ECS/System/SystemManager.cpp

CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Game/tank90-FE/Source/ECS/System/SystemManager.cpp > CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.i

CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Game/tank90-FE/Source/ECS/System/SystemManager.cpp -o CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.s

# Object files for target Tank98
Tank98_OBJECTS = \
"CMakeFiles/Tank98.dir/Source/main.cpp.o" \
"CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o" \
"CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o" \
"CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o" \
"CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o" \
"CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o" \
"CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o"

# External object files for target Tank98
Tank98_EXTERNAL_OBJECTS =

Tank98: CMakeFiles/Tank98.dir/Source/main.cpp.o
Tank98: CMakeFiles/Tank98.dir/Source/Math/Vector2.cpp.o
Tank98: CMakeFiles/Tank98.dir/Source/ECS/Component/Component.cpp.o
Tank98: CMakeFiles/Tank98.dir/Source/ECS/Entity/Entity.cpp.o
Tank98: CMakeFiles/Tank98.dir/Source/ECS/Entity/EntityManager.cpp.o
Tank98: CMakeFiles/Tank98.dir/Source/ECS/System/System.cpp.o
Tank98: CMakeFiles/Tank98.dir/Source/ECS/System/SystemManager.cpp.o
Tank98: CMakeFiles/Tank98.dir/build.make
Tank98: /usr/lib/x86_64-linux-gnu/libSDL2.so
Tank98: CMakeFiles/Tank98.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Tank98"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tank98.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tank98.dir/build: Tank98
.PHONY : CMakeFiles/Tank98.dir/build

CMakeFiles/Tank98.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tank98.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tank98.dir/clean

CMakeFiles/Tank98.dir/depend:
	cd /mnt/d/Game/tank90-FE/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Game/tank90-FE /mnt/d/Game/tank90-FE /mnt/d/Game/tank90-FE/cmake-build-debug /mnt/d/Game/tank90-FE/cmake-build-debug /mnt/d/Game/tank90-FE/cmake-build-debug/CMakeFiles/Tank98.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tank98.dir/depend

