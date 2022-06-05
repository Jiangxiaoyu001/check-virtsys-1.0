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



#SET(PROTOCOLS_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/protoclos/")

FILE(GLOB TCP_SOURCE_FILES "../protocols/tcp-client.cpp")

message(STATUS ${TCP_SOURCE_FILES})

#add source directrory
aux_source_directory(. DIR_SRCS_RemoteConnect)

#create share library can be used by others
#add_library(remoteConnectCtrLib SHARED ${DIR_SRCS})


include_directories(${PROJECT_SOURCE_DIR}/../../include)
# Tell CMake to create the virtsysManage executable
add_executable(remoteConnectCtr ${TCP_SOURCE_FILES} ${DIR_SRCS_RemoteConnect})

#add_executable(tcpserver ${TCP_SOURCE_FILES})
#add_executable(tcpclient ${TCPCLIENT_SOURCE_FILES})
#add_executable(socketmg ${SOCKET_SOURCE_FILES})



#add header files directory for target 
target_include_directories(remoteConnectCtr PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(remoteConnectCtr pthread)
target_link_libraries(remoteConnectCtr Qt5::Widgets Qt5::Core)

