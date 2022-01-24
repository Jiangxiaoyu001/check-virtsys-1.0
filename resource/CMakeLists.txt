cmake_minimum_required(VERSION 2.8.11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Core)


#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})

#add source directrory
aux_source_directory(. DIR_SECS_RESOURCES)

#create share library can be used by others
add_library(resourcesLib ${DIR_SRCS_RESOURCES})

#target_link_libraries(xxxLib Qt5::Widgets Qt5::Core)
