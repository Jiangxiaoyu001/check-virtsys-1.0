#----------------------------------------------
#	root CMakeList.txt for virsysManage
#	Author: jiangxiaoyu
#	Date: Wed Mar 2022
#----------------------------------------------



# Disable in-source builds to prevent source tree corruption.
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	 message(FATAL_ERROR "FATAL: In-source builds are not allowed.
        You should create a separate directory for build files.")
 endif()

cmake_minimum_required(VERSION 2.8.11)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

PROJECT(virCloudManage)

SET(CMAKE_BUILD_TYPE Release)


# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

# set  Qt installation
SET(CMAKE_PREFIX_PATH "~/Qt5.9.9/5.9.9/gcc_64/lib/cmake")

SET(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}")



#添加C++11支持及其他选项
SET(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./out)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./out)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./out)


SET(CMAKE_INSTALL_LIBDIR "/usr/local/lib/vircloud-manage")
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")
endif("${isSystemDir}" STREQUAL "-1")





# add sub dir
ADD_SUBDIRECTORY(src output)
ADD_SUBDIRECTORY(resource)

# add source directory
AUX_SOURCE_DIRECTORY(. DIR_SRCS_ROOT)


INCLUDE(deb) #build/deb.cmake
INCLUDE(CPack)
