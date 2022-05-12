#----------------------------------------------
#	deb  cmake for virsysManage
#	Author: jiangxiaoyu
#	Date: Fir Mar 2022
#----------------------------------------------



project(virCloudManage)

SET(CMAKE_BUILD_TYPE Release)

SET(MAJOR_VERSION 1)
SET(MINOR_VERSION 0)
SET(PATCH_VERSION 11)
SET(CPACK_GENERATOR "DEB")

##############设置debian/control文件中的内容###############

#设置版本信息
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")


#设置安装包的包名，打好的包将会是packagename-version-linux.deb，如果不设置，默认是工程名
SET(CPACK_PACKAGE_NAME "vircloud-manage")

#设置程序名，就是程序安装后的名字
SET(CPACK_DEBIAN_PACKAGE_NAME "vircloud-manage")

SET(CPACK_DEBIAN_PACKAGE_SOURCE "vircloud-manage")

#设置架构
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

#设置依赖
SET(CPACK_DEBIAN_PACKAGE_DEPENDS
				"libc6 (>= 2.3.1-6),
				libvirt-dev (>= 2.3.1)"
				)

#设置description
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "free tool to virtual system manage,still in developing")

#设置联系方式
SET(CPACK_PACKAGE_CONTACT "jiangxiaoyu@Work.com")

#设置维护人
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "jiangxiaoyu")


##############debian/control设置完成了，下面设置控制脚本，动态库，changelog等#################

#lib目录下保存这一些动态库和安装控制脚本（postinst、postrm、preinst、prerm）  
#doc目录下是changelog和copyright等文件
SET(LIBS_DIR "$ENV{DBXML_DIR}/lib")
SET(DOCS_DIR ${CMAKE_SOURCE_DIR}/doc)

#将pro-cc.conf文件安装时copy到/etc/init下
#INSTALL(FILES ${CMAKE_SOURCE_DIR}/pro-cc.conf DESTINATION /etc/init)

#将库文件安装到/usr/lib下
#INSTALL(FILES ${LIBS_DIR}/libdb-4.8.so ${LIBS_DIR}/libdbxml-2.5.so ${LIBS_DIR}/libxerces-c-3.0.so ${LIBS_DIR}/libxqilla.so.5 ${LIBS_DIR}/libxqilla.so.5.0.2  DESTINATION /usr/lib)


#设置section
SET(CPACK_DEBIAN_PACKAGE_SECTION "admin")

#设置priority
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "Optional")

SET(TARGET "vircloud-manage")
SET(APPLICATIONS "applications")
FILE(GLOB 3rdLib "${PROJECT_SOURCE_DIR}/3rdlib/*")
SET(ICONS "${PROJECT_SOURCE_DIR}/icons")
SET(DATA "${PROJECT_SOURCE_DIR}/data")
SET(RESOURCES "${PROJECT_SOURCE_DIR}/resource")
SET(CMAKE_INSTALL_BINDIR "/usr/local/bin")
SET(CMAKE_INSTALL_LIBDIR "/usr/local/lib/vircloud-manage")
SET(CMAKE_INSTALL_SHAREDIR "/usr/local/share")
SET(CMAKE_INSTALL_ICONSDIR "/usr/local/share/icons/vircloud-manage")
SET(CMAKE_INSTALL_TARGETDIR "${CMAKE_INSTALL_SHAREDIR}/${TARGET}")
SET(CMAKE_INSTALL_APPLICATIONSDIR "${CMAKE_INSTALL_TARGETDIR}/${APPLICATIONS}")


###### install 

#-------------------------------INSTALL TARGETS-----------------------------
#
#	install(TARGETS targets... [EXPORT <export-name>]
#        [RUNTIME_DEPENDENCIES args...|RUNTIME_DEPENDENCY_SET <set-name>]
#        [[ARCHIVE|LIBRARY|RUNTIME|OBJECTS|FRAMEWORK|BUNDLE|
#          PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE|FILE_SET <set-name>]
#         [DESTINATION <dir>]
#         [PERMISSIONS permissions...]
#         [CONFIGURATIONS [Debug|Release|...]]
#         [COMPONENT <component>]
#         [NAMELINK_COMPONENT <component>]
#         [OPTIONAL] [EXCLUDE_FROM_ALL]
#         [NAMELINK_ONLY|NAMELINK_SKIP]
#        ] [...]
#        [INCLUDES DESTINATION [<dir> ...]]
#        )
#--------------------------------------------------------

INSTALL(TARGETS virCloudManage checkVirSysLib 
		widgetsLib
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#-----------------------INSTALL DIRECTORIES------------------
#
#	install(DIRECTORY dirs...
#		TYPE <type> | DESTINATION <dir>
#        [FILE_PERMISSIONS permissions...]
#        [DIRECTORY_PERMISSIONS permissions...]
#        [USE_SOURCE_PERMISSIONS] [OPTIONAL] [MESSAGE_NEVER]
#        [CONFIGURATIONS [Debug|Release|...]]
#        [COMPONENT <component>] [EXCLUDE_FROM_ALL]
#        [FILES_MATCHING]
#        [[PATTERN <pattern> | REGEX <regex>]
#         [EXCLUDE] [PERMISSIONS permissions...]] [...])
#---------------------------------------------------------------------



#-------------------------install file-------------
#
#	install(<FILES|PROGRAMS> files... DESTINATION <dir>
#        [PERMISSIONS permissions...]
#        [CONFIGURATIONS [Debug|Release|...]]
#        [COMPONENT <component>]
#        [RENAME <name>] [OPTIONAL])
#
#-------------------------------------------------------
#
#
INSTALL(FILES ${3rdLib} DESTINATION ${CMAKE_INSTALL_LIBDIR})




INSTALL(DIRECTORY "${ICONS}/"
		DESTINATION "/usr/local/share/vircloud-manage/icons")

INSTALL(DIRECTORY "${DATA}/"
		DESTINATION ${CMAKE_INSTALL_APPLICATIONSDIR})

INSTALL(DIRECTORY "${RESOURCES}/"
		#DESTINATION ${CMAKE_INSTALL_TARGETDIR})
		DESTINATION "/usr/local/share/vircloud-manage/resource")

#--------------- make uninstall------------------------------

ADD_CUSTOM_TARGET("uninstall" COMMENT "Uninstall installed files")

ADD_CUSTOM_COMMAND(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
   
	#COMMAND rm -vf ${CMAKE_INSTALL_ICONSDIR}
	#				${CMAKE_INSTALL_TARGETDIR}
	#				${CMAKE_INSTALL_LIBDIR}
	#				/usr/local/bin/virCloudManage
)

# use, i.e. don't skip the full RPATH for the build tree
#set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

#set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")

# 	add the automatically determined parts of the RPATH
#	which point to directories outside the build tree to the install RPATH
#	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
#	list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_LIBDIR}" isSystemDir)
#	if("${isSystemDir}" STREQUAL "-1")
#	set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")
#	endif("${isSystemDir}" STREQUAL "-1")

