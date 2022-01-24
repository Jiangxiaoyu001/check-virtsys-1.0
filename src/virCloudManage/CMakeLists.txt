#----------------------------------------------
#	major CMakeList.txt for virsysManage
#	Author: jiangxiaoyu
#	Date: Wed Mar 2022
#----------------------------------------------


cmake_minimum_required(VERSION 2.8.11)

#project(virCloudManage)


# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Xml)
find_package(Qt5Widgets)
find_package(Qt5Core)


#if(Qt5_FOUND)
# find_package_message(Qt5 "Found Qt5: ${Qt5_Qt5_LIB}"
#   "[${Qt5_Qt5_LIB}][${Qt5_INCLUDE_DIR}]")
#endif()
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# set  Qt installation
set(CMAKE_PREFIX_PATH "~/Qt5.9.9/5.9.9/gcc_64/lib/cmake")



#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add header files dir
#INCLUDE_DIRECTORIES(include)

FILE(GLOB VIRCM_RESOURCE "${PROJECT_SOURCE_DIR}/resource/*.qrc")

# add source directory
aux_source_directory(. DIR_SRCS_ROOT)

# Tell CMake to create the virtsysManage executable
add_executable(virCloudManage ${DIR_SRCS_ROOT} ${VIRCM_RESOURCE})


# Use the lib
target_link_libraries(virCloudManage widgetsLib checkVirSysLib 3rdLib)
target_link_libraries(virCloudManage Qt5::Widgets Qt5::Core)

# if using Cmake older than 2.8.9 should use target_link_libraries to replace 
#qt5_use_modules(virCloudManage Widgets Sql Network Xml Gui Core Charts)
