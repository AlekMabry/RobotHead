cmake_minimum_required(VERSION 3.1)
PROJECT ( AudioModule )
set( CMAKE_BUILD_TYPE Release )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" )

include(FindPkgConfig)

find_package( PkgConfig REQUIRED )
find_package( PocketSphinx REQUIRED )

set( NAME_SRC
        AudioManager.cpp
        )

set( NAME_HEADERS
        AudioManager.h
        )

# Link PocketSphinx
include_directories( ${POCKETSPHINX_INCLUDE_DIRS} )
link_directories( ${POCKETSPHINX_INCLUDE_DIRS} )
# target_link_libraries( AudioModule ${POCKETSPHINX_LIBRARIES} )
# add_compile_options( -DMODELDIR=${POCKETSPHINX_MODELDIR})

# Create the Library
add_library( AudioModule SHARED ${NAME_SRC} ${NAME_HEADERS} )
