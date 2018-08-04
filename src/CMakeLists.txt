cmake_minimum_required(VERSION 3.1)
PROJECT (roboCore)

list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" )

include(FindPkgConfig)

find_package( OpenCV REQUIRED )
find_package( PkgConfig REQUIRED )
find_package( AudioModule REQUIRED )

set( NAME_SRC
        roboCore.cpp
        BlobDetection.cpp
        FaceDetection.cpp
        )

set( NAME_HEADERS
        BlobDetection.h
        FaceDetection.h
        )

add_executable( roboCore ${NAME_SRC} ${NAME_HEADERS} )
include_directories( ${AUDIOMODULE_INCLUDE_DIR} )
target_link_libraries( roboCore ${OpenCV_LIBS} ${AUDIOMODULE_LIBRARY} )
