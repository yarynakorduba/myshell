# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/yuriy/CLion/clion-2016.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/yuriy/CLion/clion-2016.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yuriy/CLionProjects/myCP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuriy/CLionProjects/myCP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/myCP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myCP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myCP.dir/flags.make

CMakeFiles/myCP.dir/main.cpp.o: CMakeFiles/myCP.dir/flags.make
CMakeFiles/myCP.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuriy/CLionProjects/myCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myCP.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myCP.dir/main.cpp.o -c /home/yuriy/CLionProjects/myCP/main.cpp

CMakeFiles/myCP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myCP.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuriy/CLionProjects/myCP/main.cpp > CMakeFiles/myCP.dir/main.cpp.i

CMakeFiles/myCP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myCP.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuriy/CLionProjects/myCP/main.cpp -o CMakeFiles/myCP.dir/main.cpp.s

CMakeFiles/myCP.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/myCP.dir/main.cpp.o.requires

CMakeFiles/myCP.dir/main.cpp.o.provides: CMakeFiles/myCP.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/myCP.dir/build.make CMakeFiles/myCP.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/myCP.dir/main.cpp.o.provides

CMakeFiles/myCP.dir/main.cpp.o.provides.build: CMakeFiles/myCP.dir/main.cpp.o


# Object files for target myCP
myCP_OBJECTS = \
"CMakeFiles/myCP.dir/main.cpp.o"

# External object files for target myCP
myCP_EXTERNAL_OBJECTS =

myCP: CMakeFiles/myCP.dir/main.cpp.o
myCP: CMakeFiles/myCP.dir/build.make
myCP: CMakeFiles/myCP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuriy/CLionProjects/myCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable myCP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myCP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myCP.dir/build: myCP

.PHONY : CMakeFiles/myCP.dir/build

CMakeFiles/myCP.dir/requires: CMakeFiles/myCP.dir/main.cpp.o.requires

.PHONY : CMakeFiles/myCP.dir/requires

CMakeFiles/myCP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myCP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myCP.dir/clean

CMakeFiles/myCP.dir/depend:
	cd /home/yuriy/CLionProjects/myCP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuriy/CLionProjects/myCP /home/yuriy/CLionProjects/myCP /home/yuriy/CLionProjects/myCP/cmake-build-debug /home/yuriy/CLionProjects/myCP/cmake-build-debug /home/yuriy/CLionProjects/myCP/cmake-build-debug/CMakeFiles/myCP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myCP.dir/depend
