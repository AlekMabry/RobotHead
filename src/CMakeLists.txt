cmake_minimum_required(VERSION 3.1)
PROJECT (roboCore)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" )

include(FindPkgConfig)

find_package( OpenCV REQUIRED )
find_package( PkgConfig REQUIRED )
# find_package( AudioModule REQUIRED )

# find_package( AudioModule REQUIRED )
# set( AUDIOMODULE_LIBRARY libAudioModule.so )
# link_directories( ../AudioModule )
# include_directories( ../AudioModule )

set( NAME_SRC
        roboCore.cpp
        BlobDetection.cpp
        FaceDetection.cpp
        servos.cpp
        )

set( NAME_HEADERS
        BlobDetection.h
        FaceDetection.h
        servos.h
        )

add_executable( roboCore ${NAME_SRC} ${NAME_HEADERS} )
# include_directories( ${AUDIOMODULE_INCLUDE_DIR} )
target_link_libraries( roboCore ${OpenCV_LIBS} )
# target_link_libraries( roboCore ${OpenCV_LIBS} ${AUDIOMODULE_LIBRARY} )
# target_link_libraries( roboCore ${OpenCV_LIBS} ${PROJECT_LINK_LIBS})
