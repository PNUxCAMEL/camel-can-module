# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /snap/clion/184/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/184/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jaehyung/camel-can-module

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaehyung/camel-can-module/cmake-build-release

# Include any dependencies generated for this target.
include matplotlib-cpp/examples/CMakeFiles/modern.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include matplotlib-cpp/examples/CMakeFiles/modern.dir/compiler_depend.make

# Include the progress variables for this target.
include matplotlib-cpp/examples/CMakeFiles/modern.dir/progress.make

# Include the compile flags for this target's objects.
include matplotlib-cpp/examples/CMakeFiles/modern.dir/flags.make

matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.o: matplotlib-cpp/examples/CMakeFiles/modern.dir/flags.make
matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.o: ../matplotlib-cpp/examples/modern.cpp
matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.o: matplotlib-cpp/examples/CMakeFiles/modern.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaehyung/camel-can-module/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.o"
	cd /home/jaehyung/camel-can-module/cmake-build-release/matplotlib-cpp/examples && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.o -MF CMakeFiles/modern.dir/modern.cpp.o.d -o CMakeFiles/modern.dir/modern.cpp.o -c /home/jaehyung/camel-can-module/matplotlib-cpp/examples/modern.cpp

matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modern.dir/modern.cpp.i"
	cd /home/jaehyung/camel-can-module/cmake-build-release/matplotlib-cpp/examples && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaehyung/camel-can-module/matplotlib-cpp/examples/modern.cpp > CMakeFiles/modern.dir/modern.cpp.i

matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modern.dir/modern.cpp.s"
	cd /home/jaehyung/camel-can-module/cmake-build-release/matplotlib-cpp/examples && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaehyung/camel-can-module/matplotlib-cpp/examples/modern.cpp -o CMakeFiles/modern.dir/modern.cpp.s

# Object files for target modern
modern_OBJECTS = \
"CMakeFiles/modern.dir/modern.cpp.o"

# External object files for target modern
modern_EXTERNAL_OBJECTS =

matplotlib-cpp/examples/modern: matplotlib-cpp/examples/CMakeFiles/modern.dir/modern.cpp.o
matplotlib-cpp/examples/modern: matplotlib-cpp/examples/CMakeFiles/modern.dir/build.make
matplotlib-cpp/examples/modern: /usr/lib/x86_64-linux-gnu/libpython3.6m.so
matplotlib-cpp/examples/modern: matplotlib-cpp/examples/CMakeFiles/modern.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaehyung/camel-can-module/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable modern"
	cd /home/jaehyung/camel-can-module/cmake-build-release/matplotlib-cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modern.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
matplotlib-cpp/examples/CMakeFiles/modern.dir/build: matplotlib-cpp/examples/modern
.PHONY : matplotlib-cpp/examples/CMakeFiles/modern.dir/build

matplotlib-cpp/examples/CMakeFiles/modern.dir/clean:
	cd /home/jaehyung/camel-can-module/cmake-build-release/matplotlib-cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/modern.dir/cmake_clean.cmake
.PHONY : matplotlib-cpp/examples/CMakeFiles/modern.dir/clean

matplotlib-cpp/examples/CMakeFiles/modern.dir/depend:
	cd /home/jaehyung/camel-can-module/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaehyung/camel-can-module /home/jaehyung/camel-can-module/matplotlib-cpp/examples /home/jaehyung/camel-can-module/cmake-build-release /home/jaehyung/camel-can-module/cmake-build-release/matplotlib-cpp/examples /home/jaehyung/camel-can-module/cmake-build-release/matplotlib-cpp/examples/CMakeFiles/modern.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : matplotlib-cpp/examples/CMakeFiles/modern.dir/depend

