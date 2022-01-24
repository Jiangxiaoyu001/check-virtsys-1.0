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


#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})


#get_target_property(QtCore_location Qt5::Core LOCATION)
#qt5_use_modules(virsysManage Widgets Sql Network Xml Gui Core Qchart)

#add header files directory
include_directories(${PROJECT_SOURCE_DIR}/include)

#add source directrory
aux_source_directory(. DIR_SECS_3RD)

#create share library can be used by others
add_library(3rdLib ${DIR_SRCS_3RD})

#target_link_libraries(xxxLib Qt5::Widgets Qt5::Core)
