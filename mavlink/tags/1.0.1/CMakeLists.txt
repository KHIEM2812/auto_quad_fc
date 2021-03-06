project (mavlink NONE)

# settings
cmake_minimum_required (VERSION 2.8.2)
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_CONTACT_EMAIL http://groups.google.com/group/mavlink)
set(PROJECT_CONTACT_VENDOR mavlink)
set(LIBRARY_VERSION ${PROJECT_VERSION})
set(LIBRARY_SOVERSION "0.0.0")

# third party 
# none required

# options
option(WITH_TESTS "Build test programs." OFF)
option(WITH_BUILD_DEPS "Build dependencies." OFF) # no deps currently to build
option(WITH_BUILD_STATIC "Build preferring static linking." ON)

# variables
set(ROOT_THREAD TRUE CACHE INTERNAL "Is this the top level of the recursion?")
set(INSTALLED_TARGETS "")

# modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#include(CheckIncludeFiles)
#include(CheckFunctionExists)
#include(CheckSymbolExists)
#include(CheckLibraryExists)
#include(CheckTypeSize)
#include(CheckPrototypeExists)
#include(CheckCXXSourceCompiles)
#include(CheckCSourceCompiles)
include(ExternalProject)

# spawn new cmake to build deps
if (WITH_BUILD_DEPS AND ROOT_THREAD)
    execute_process(COMMAND ${CMAKE_COMMAND} "${CMAKE_SOURCE_DIR}"
        "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
        "-DWITH_BUILD_DEPS=${WITH_BUILD_DEPS}"
        "-DWITH_BUILD_STATIC=${WITH_BUILD_STATIC}"
        "-DWITH_TESTS=${WITH_TESTS}"
        "-DROOT_THREAD=FALSE"
        RESULT_VARIABLE ERROR)
    if (ERROR)
        message(FATAL_ERROR "error, recursing loop returned error code: ${ERROR}")
    endif()
    message("** Making dependencies")
    execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} "-j4" "-f${CMAKE_BINARY_DIR}/Makefile")
    message("** Configuring ${PROJECT_NAME}")
endif()

# external projects find path
if(NOT EP_BASE_DIR)
    set(EP_BASE_DIR "${CMAKE_BINARY_DIR}/CMakeExternals")
endif()
list(APPEND CMAKE_FIND_ROOT_PATH ${EP_BASE_DIR})

# prefer static packages if building static library
message("** Finding libraries")
if (WITH_BUILD_STATIC)
    # prefer static libs
    if(WIN32)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    endif()
endif()

# find libraries with cmake modules
find_package(PythonInterp)

# enable languages
if (WITH_TESTS)
    enable_language(C)
    enable_language(CXX)
    include(DefineCompilerFlags)
endif()

# build dependencies
if (WITH_BUILD_DEPS AND (NOT ROOT_THREAD) )
    message("** Configuring dependencies")

    # add external projects

    # none required currently

    set(CMAKE_DEFAULT_ARGS
        -DEP_BASE_DIR=${EP_BASE_DIR}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        )

    # terminate non root cmake thread
    return()
endif()

# configure
#check_include_files(string.h HAVE_STRING_H)
#check_function_exists(memcopy HAVE_MEMCOPY)
#check_symbol_exists(LC_MESSAGES "locale.h" HAVE_LC_MESSAGES) 
#check_library_exists(pthread  attachNode "" HAVE_PTHREAD)

# config files
configure_file(config.h.in config.h)

# mavlink generation
macro(generateMavlink version definitions)
    foreach(definition ${definitions})
        set(targetName ${definition}-v${version})
        set(definitionAbsPath ${CMAKE_SOURCE_DIR}/message_definitions/v${version}/${definition})
        message(STATUS "processing: ${definitionAbsPath}")
        add_custom_command( 
            OUTPUT ${targetName}-stamp
            COMMAND ${PYTHON_EXECUTABLE} ${mavgen} --lang=C --wire-protocol=${version}
                --output=include/v${version} ${definitionAbsPath}
            COMMAND touch ${targetName}-stamp
            DEPENDS ${definitionAbsPath} ${mavgen}
            )
        add_custom_target(${targetName} ALL DEPENDS ${targetName}-stamp)
    endforeach()
endmacro()

# build
set(mavgen ${CMAKE_CURRENT_SOURCE_DIR}/pymavlink/generator/mavgen.py)
set(v0.9Definitions
    ardupilotmega.xml
    common.xml
    minimal.xml
    pixhawk.xml
    slugs.xml
    test.xml
    ualberta.xml
    )
generateMavlink("0.9" "${v0.9Definitions}")
set(v1.0Definitions
    ardupilotmega.xml
    common.xml
    matrixpilot.xml
    minimal.xml
    pixhawk.xml
    slugs.xml
    test.xml
    ualberta.xml
    )
generateMavlink("1.0" "${v1.0Definitions}")

# testing
if (BUILD_TEST)
    if (UNIX) 
        include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/v0.9/common)
        # TODO fix udp example
        #add_executable(mavlink_udp examples/linux/mavlink_udp.c)
    endif()
endif()

# install files
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/ DESTINATION include/${PROJECT_NAME} COMPONENT dev FILES_MATCHING PATTERN "*.h")

# install
install(TARGETS  ${INSTALLED_TARGETS}
    RUNTIME DESTINATION "bin" COMPONENT Runtime
    LIBRARY DESTINATION "lib" COMPONENT Runtime
    ARCHIVE DESTINATION "lib" COMPONENT Dev
    BUNDLE DESTINATION "/Applications" COMPONENT Runtime
    FRAMEWORK DESTINATION "/Library/Frameworks" COMPONENT Runtime
    # where to put files on non-mac computers, mac overrides and uses default
    PRIVATE_HEADER DESTINATION "include/${PROJECT_NAME}" COMPONENT Runtime
    PUBLIC_HEADER DESTINATION "include/${PROJECT_NAME}" COMPONENT Runtime
    RESOURCE DESTINATION "share/${PROJECT_NAME}" COMPONENT Runtime
    )

# install external projects, if built
if (EXISTS ${EP_BASE_DIR}/${CMAKE_INSTALL_PREFIX}/)
    install(DIRECTORY ${EP_BASE_DIR}/${CMAKE_INSTALL_PREFIX}/ DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT Runtime)
endif()

### packaging

# apple bundle icon
if (APPLE)
    # set how it shows up in Info.plist
    set(MACOSX_BUNDLE_ICON_FILE mavlink.icns)
    # set where in the bundle to put the icns file
    set_source_files_properties(cmake/mavlink.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    # include the icns file in the target
    #list(APPEND MAVLINKGUI_SRCS cmake/mavlink.icns)
endif()

# set NSIS image
if (WIN32)
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/cmake/mavlink.bmp")
endif()

# add file extensions and set resource files
configure_file("COPYING" "COPYING.txt" COPYONLY)
configure_file("README" "README.txt" COPYONLY)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/COPYING.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_BINARY_DIR}/README.txt")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CPACK_RESOURCE_FILE_README}")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/cmake/WELCOME.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "mavlink message marshalling library")
set(CPACK_PACKAGE_VENDOR ${PROJECT_CONTACT_VENDOR})
set(CPACK_PACKAGE_CONTACT "${PROJECT_CONTACT_EMAIL}")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_SET_DESTDIR TRUE)
set(CPACK_COMPONENTS_GROUPING "ALL_COMPONENTS_IN_ONE")
include(CPack)

# pkgconfig
configure_file(pc.in ${PROJECT_NAME}.pc)
install(FILES
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION "lib/pkgconfig" COMPONENT Dev
    )
# vim:sw=4:ts=4:expandtab
