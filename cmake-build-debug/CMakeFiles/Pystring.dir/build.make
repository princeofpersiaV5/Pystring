# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/145/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/145/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wulezhou/CLionProjects/Pystring

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wulezhou/CLionProjects/Pystring/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Pystring.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Pystring.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Pystring.dir/flags.make

CMakeFiles/Pystring.dir/pystring.cpp.o: CMakeFiles/Pystring.dir/flags.make
CMakeFiles/Pystring.dir/pystring.cpp.o: ../pystring.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wulezhou/CLionProjects/Pystring/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Pystring.dir/pystring.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Pystring.dir/pystring.cpp.o -c /home/wulezhou/CLionProjects/Pystring/pystring.cpp

CMakeFiles/Pystring.dir/pystring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pystring.dir/pystring.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wulezhou/CLionProjects/Pystring/pystring.cpp > CMakeFiles/Pystring.dir/pystring.cpp.i

CMakeFiles/Pystring.dir/pystring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pystring.dir/pystring.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wulezhou/CLionProjects/Pystring/pystring.cpp -o CMakeFiles/Pystring.dir/pystring.cpp.s

# Object files for target Pystring
Pystring_OBJECTS = \
"CMakeFiles/Pystring.dir/pystring.cpp.o"

# External object files for target Pystring
Pystring_EXTERNAL_OBJECTS =

Pystring: CMakeFiles/Pystring.dir/pystring.cpp.o
Pystring: CMakeFiles/Pystring.dir/build.make
Pystring: CMakeFiles/Pystring.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wulezhou/CLionProjects/Pystring/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Pystring"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Pystring.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Pystring.dir/build: Pystring

.PHONY : CMakeFiles/Pystring.dir/build

CMakeFiles/Pystring.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Pystring.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Pystring.dir/clean

CMakeFiles/Pystring.dir/depend:
	cd /home/wulezhou/CLionProjects/Pystring/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wulezhou/CLionProjects/Pystring /home/wulezhou/CLionProjects/Pystring /home/wulezhou/CLionProjects/Pystring/cmake-build-debug /home/wulezhou/CLionProjects/Pystring/cmake-build-debug /home/wulezhou/CLionProjects/Pystring/cmake-build-debug/CMakeFiles/Pystring.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Pystring.dir/depend

