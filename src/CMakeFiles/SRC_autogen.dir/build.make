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

# Utility rule file for SRC_autogen.

# Include the progress variables for this target.
include src/CMakeFiles/SRC_autogen.dir/progress.make

src/CMakeFiles/SRC_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target SRC"
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src && /usr/bin/cmake -E cmake_autogen /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/CMakeFiles/SRC_autogen.dir/AutogenInfo.json ""

SRC_autogen: src/CMakeFiles/SRC_autogen
SRC_autogen: src/CMakeFiles/SRC_autogen.dir/build.make

.PHONY : SRC_autogen

# Rule to build all files generated by this target.
src/CMakeFiles/SRC_autogen.dir/build: SRC_autogen

.PHONY : src/CMakeFiles/SRC_autogen.dir/build

src/CMakeFiles/SRC_autogen.dir/clean:
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src && $(CMAKE_COMMAND) -P CMakeFiles/SRC_autogen.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/SRC_autogen.dir/clean

src/CMakeFiles/SRC_autogen.dir/depend:
	cd /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0 /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0 /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/CMakeFiles/SRC_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/SRC_autogen.dir/depend

