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
CMAKE_BINARY_DIR = /home/jaehyung/camel-can-module/cmake-build-debug

# Include any dependencies generated for this target.
include matplotlib-cpp/examples/CMakeFiles/spy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include matplotlib-cpp/examples/CMakeFiles/spy.dir/compiler_depend.make

# Include the progress variables for this target.
include matplotlib-cpp/examples/CMakeFiles/spy.dir/progress.make

# Include the compile flags for this target's objects.
include matplotlib-cpp/examples/CMakeFiles/spy.dir/flags.make

matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.o: matplotlib-cpp/examples/CMakeFiles/spy.dir/flags.make
matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.o: ../matplotlib-cpp/examples/spy.cpp
matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.o: matplotlib-cpp/examples/CMakeFiles/spy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaehyung/camel-can-module/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.o"
	cd /home/jaehyung/camel-can-module/cmake-build-debug/matplotlib-cpp/examples && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.o -MF CMakeFiles/spy.dir/spy.cpp.o.d -o CMakeFiles/spy.dir/spy.cpp.o -c /home/jaehyung/camel-can-module/matplotlib-cpp/examples/spy.cpp

matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spy.dir/spy.cpp.i"
	cd /home/jaehyung/camel-can-module/cmake-build-debug/matplotlib-cpp/examples && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaehyung/camel-can-module/matplotlib-cpp/examples/spy.cpp > CMakeFiles/spy.dir/spy.cpp.i

matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spy.dir/spy.cpp.s"
	cd /home/jaehyung/camel-can-module/cmake-build-debug/matplotlib-cpp/examples && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaehyung/camel-can-module/matplotlib-cpp/examples/spy.cpp -o CMakeFiles/spy.dir/spy.cpp.s

# Object files for target spy
spy_OBJECTS = \
"CMakeFiles/spy.dir/spy.cpp.o"

# External object files for target spy
spy_EXTERNAL_OBJECTS =

matplotlib-cpp/examples/spy: matplotlib-cpp/examples/CMakeFiles/spy.dir/spy.cpp.o
matplotlib-cpp/examples/spy: matplotlib-cpp/examples/CMakeFiles/spy.dir/build.make
matplotlib-cpp/examples/spy: /usr/lib/x86_64-linux-gnu/libpython3.6m.so
matplotlib-cpp/examples/spy: matplotlib-cpp/examples/CMakeFiles/spy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaehyung/camel-can-module/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable spy"
	cd /home/jaehyung/camel-can-module/cmake-build-debug/matplotlib-cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
matplotlib-cpp/examples/CMakeFiles/spy.dir/build: matplotlib-cpp/examples/spy
.PHONY : matplotlib-cpp/examples/CMakeFiles/spy.dir/build

matplotlib-cpp/examples/CMakeFiles/spy.dir/clean:
	cd /home/jaehyung/camel-can-module/cmake-build-debug/matplotlib-cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/spy.dir/cmake_clean.cmake
.PHONY : matplotlib-cpp/examples/CMakeFiles/spy.dir/clean

matplotlib-cpp/examples/CMakeFiles/spy.dir/depend:
	cd /home/jaehyung/camel-can-module/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaehyung/camel-can-module /home/jaehyung/camel-can-module/matplotlib-cpp/examples /home/jaehyung/camel-can-module/cmake-build-debug /home/jaehyung/camel-can-module/cmake-build-debug/matplotlib-cpp/examples /home/jaehyung/camel-can-module/cmake-build-debug/matplotlib-cpp/examples/CMakeFiles/spy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : matplotlib-cpp/examples/CMakeFiles/spy.dir/depend

