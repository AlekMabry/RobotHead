# Find AudioModule Library
set( FIND_AUDIOMODULE_PATHS ../AudioModule )
find_path( AUDIOMODULE_INCLUDE_DIR AudioManager.h
            PATHS ${FIND_AUDIOMODULE_PATHS})
find_library( AUDIOMODULE_LIBRARY
            NAMES AudioModule
            PATHS ${FIND_AUDIOMODULE_PATHS} )
