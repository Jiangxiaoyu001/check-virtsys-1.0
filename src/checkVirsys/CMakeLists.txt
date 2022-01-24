cmake_minimum_required(VERSION 2.8.11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

# Find the lib/ QtWidgets library
find_package(Qt5Xml)
find_package(Qt5Charts)
find_package(Qt5Widgets)
find_package(Qt5Core)
#find_package(CMAKE_DL_LIBS)

#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})



# add header files directrory
include_directories(${PROJECT_SOURCE_DIR}/include)

FILE(GLOB HEADER_FILE "${PROJECT_SOURCE_DIR}/include/checkVirsys/*.h")
#add source dir
aux_source_directory(. DIR_SRCS_CHECKVIRSYS)

#create share library can be used by others
add_library(checkVirSysLib SHARED ${DIR_SRCS_CHECKVIRSYS} ${HEADER_FILE})

target_link_libraries(checkVirSysLib widgetsLib ${CMAKE_DL_LIBS} libvirt.so)
target_link_libraries(checkVirSysLib Qt5::Xml Qt5::Widgets Qt5::Core Qt5::Charts)
