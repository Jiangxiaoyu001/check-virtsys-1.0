cmake_minimum_required(VERSION 2.8.11)


# Find the QtWidgets library
find_package(Qt5Xml)
find_package(Qt5Widgets)
find_package(Qt5Core)




# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)


#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")


#get_target_property(QtCore_location Qt5::Core LOCATION)
#qt5_use_modules(virsysManage Widgets Sql Network Xml Gui Core Qchart)


FILE(GLOB HEADER_FILE "${PROJECT_SOURCE_DIR}/include/widgets/*.h")

#add source directrory
aux_source_directory(. DIR_SRCS_WIDGETS)

#create share library can be used by others
add_library(widgetsLib SHARED ${HEADER_FILE} ${DIR_SRCS_WIDGETS})

#add header files directory and lib  for target 
target_include_directories(widgetsLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(widgetsLib Qt5::Widgets Qt5::Core)
