# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0

# Include any dependencies generated for this target.
include src/widgets/CMakeFiles/mywidgets.dir/depend.make

# Include the progress variables for this target.
include src/widgets/CMakeFiles/mywidgets.dir/progress.make

# Include the compile flags for this target's objects.
include src/widgets/CMakeFiles/mywidgets.dir/flags.make

src/widgets/CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.o: src/widgets/CMakeFiles/mywidgets.dir/flags.make
src/widgets/CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.o: src/widgets/mywidgets_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/widgets/CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.o"
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.o -c /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets/mywidgets_autogen/mocs_compilation.cpp

src/widgets/CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.i"
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets/mywidgets_autogen/mocs_compilation.cpp > CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.i

src/widgets/CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.s"
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets/mywidgets_autogen/mocs_compilation.cpp -o CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.s

# Object files for target mywidgets
mywidgets_OBJECTS = \
"CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.o"

# External object files for target mywidgets
mywidgets_EXTERNAL_OBJECTS =

src/widgets/libmywidgets.a: src/widgets/CMakeFiles/mywidgets.dir/mywidgets_autogen/mocs_compilation.cpp.o
src/widgets/libmywidgets.a: src/widgets/CMakeFiles/mywidgets.dir/build.make
src/widgets/libmywidgets.a: src/widgets/CMakeFiles/mywidgets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmywidgets.a"
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets && $(CMAKE_COMMAND) -P CMakeFiles/mywidgets.dir/cmake_clean_target.cmake
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mywidgets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/widgets/CMakeFiles/mywidgets.dir/build: src/widgets/libmywidgets.a

.PHONY : src/widgets/CMakeFiles/mywidgets.dir/build

src/widgets/CMakeFiles/mywidgets.dir/clean:
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets && $(CMAKE_COMMAND) -P CMakeFiles/mywidgets.dir/cmake_clean.cmake
.PHONY : src/widgets/CMakeFiles/mywidgets.dir/clean

src/widgets/CMakeFiles/mywidgets.dir/depend:
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0 /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0 /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/widgets/CMakeFiles/mywidgets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/widgets/CMakeFiles/mywidgets.dir/depend

