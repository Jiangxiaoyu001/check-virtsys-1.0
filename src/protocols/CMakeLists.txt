cmake_minimum_required(VERSION 2.8.11)

project(remoteConnectCtl)



# set  Qt installation
SET(CMAKE_PREFIX_PATH "~/Qt5.9.9/5.9.9/gcc_64/lib/cmake")

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

 
# add C++11 support and options
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -lpthread -fprofile-arcs -Wno-deprecated")


#get_target_property(QtCore_location Qt5::Core LOCATION)
#qt5_use_modules(virsysManage Widgets Sql Network Xml Gui Core Qchart)


FILE(GLOB HEADER_FILE "${PROJECT_SOURCE_DIR}/include/widgets/*.h")

FILE(GLOB TCP_SOURCE_FILES "tcp-server.cpp")

FILE(GLOB TCPCLIENT_SOURCE_FILES "${PROJECT_SOURCE_DIR}/include/tcp-client.h"
								 "tcp-client.cpp")

FILE(GLOB SOCKET_SOURCE_FILES "socket-manage.cpp")

#add source directrory
#aux_source_directory(. DIR_SRCS_RemoteConnect)

#create share library can be used by others
#add_library(remoteConnectCtrLib SHARED ${DIR_SRCS})

# Tell CMake to create the virtsysManage executable
#add_executable(remoteConnectCtr ${DIR_SRCS})
add_executable(tcpserver ${TCP_SOURCE_FILES})
#add_executable(tcpclient ${TCPCLIENT_SOURCE_FILES})
add_executable(socketmg ${SOCKET_SOURCE_FILES})



#add header files directory for target 
#target_include_directories(widgetsLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

#target_link_libraries(remoteConnectCtr Qt5::Widgets Qt5::Core)
#target_link_libraries(remoteConnectCtrLib Qt5::Widgets Qt5::Core)

#add header files directory and libs for target 
target_link_libraries(tcpserver pthread)
#target_link_libraries(tcpclient pthread)
