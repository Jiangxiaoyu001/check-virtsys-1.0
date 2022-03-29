#------------------------------------------------------
#	
#	src CMakeLists.txt for virCLoudManage
#	Author:	jiangxiaoyu
#	Date: Wed Mar 16 2022 15:30
#
#------------------------------------------------------


cmake_minimum_required(VERSION 2.8.11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Xml)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Charts)
#find_package(libvirt)


#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})


#get_target_property(QtCore_location Qt5::Core LOCATION)
#qt5_use_modules(virsysManage Widgets Sql Network Xml Gui Core Qchart)

#FILE(GLOB SC_FILES "widgets/*.cpp" "widgets/*.h")

#add header files dir
include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(. DIR_SRCS)

#create share library can be used by others
add_library(SRCLib SHARED ${DIR_SRCS})


#---------------------------------------------------------------
# 	add sub dir 
#	add_subdirectory (source_dir [binary_dir] [EXCLUDE_FROM_ALL])
#--------------------------------------------------------------
ADD_SUBDIRECTORY(3rd)
ADD_SUBDIRECTORY(widgets)
ADD_SUBDIRECTORY(checkVirsys)
ADD_SUBDIRECTORY(virCloudManage)

#link share lib to use
#target_link_libraries(SRCLib checkVirSysLib 3rdLib widgetsLib)
#target_link_libraries(SRCLib Qt5::Widgets Qt5::Charts Qt5::Core Qt5::Xml)
