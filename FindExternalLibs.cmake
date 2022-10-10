# This file is used to configure the External libraries

# ------------------------------------------------------------------------------
# Set External libraries path
# ------------------------------------------------------------------------------
set( EXTERNAL_LIBS_DIR "/usr/local/ExternalLibs" CACHE STRING "External libs Dir" )

# ------------------------------------------------------------------------------
# set External libraries version
# ------------------------------------------------------------------------------
set( ITK_VERSION 	"5.2.1" 	CACHE STRING "ITK Version" )
set( VTK_VERSION 	"9.1.0" 	CACHE STRING "VTK Version" )

# ------------------------------------------------------------------------------
# set External libraries directories
# ------------------------------------------------------------------------------
set( ITK_DIR2 	"${EXTERNAL_LIBS_DIR}/itk" 		CACHE STRING "ITK Dir" )
set( VTK_DIR2 	"${EXTERNAL_LIBS_DIR}/vtk" 		CACHE STRING "VTK Dir" )


# ------------------------------------------------------------------------------
# QT
# ------------------------------------------------------------------------------
find_package(Qt5Core)

# ------------------------------------------------------------------------------
# OpenGL
# ------------------------------------------------------------------------------
find_package( OpenGL REQUIRED )
if( NOT OPENGL_FOUND )
    message( SEND_ERROR "OpenGL required, but not found with 'find_package()'" )
endif()

# ------------------------------------------------------------------------------
# ITK
# ------------------------------------------------------------------------------
if( NOT EXISTS ${ITK_DIR2} )
    message( SEND_ERROR "Cant't find ITK in ${EXTERNAL_LIBS_DIR}" )
else()
	set( ITK_DIR "${ITK_DIR2}/lib/cmake/ITK-5.2")
	find_package( ITK REQUIRED )
	include( ${ITK_USE_FILE} )	
endif()

# ------------------------------------------------------------------------------
# VTK
# ------------------------------------------------------------------------------
if( NOT EXISTS ${VTK_DIR2} )
    message( SEND_ERROR "Cant't find VTK in ${EXTERNAL_LIBS_DIR}" )
else()
	set( VTK_DIR "${VTK_DIR2}/lib/cmake/vtk-9.1")
	find_package( VTK REQUIRED )
	include( ${VTK_USE_FILE} )	
endif()


# ------------------------------------------------------------------------------
# GLOBAL VARIABLES
# ------------------------------------------------------------------------------
list( APPEND EXTERNAL_LIBS_INCLUDE_DIR  ${VTK_INCLUDE_DIR} ${QT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} )
if( ${MSVC} )
    list( APPEND EXTERNAL_LIBS_LIBRARIES 	${VTK_LIBRARIES} ${QT_LIBRARIES} ${ITK_LIBRARIES} ${OPENGL_LIBRARIES} wsock32 snmpapi rpcrt4 )
elseif( ${MINGW} )
    list( APPEND EXTERNAL_LIBS_LIBRARIES 	${VTK_LIBRARIES} ${QT_LIBRARIES} ${ITK_LIBRARIES} ${OPENGL_LIBRARIES})
else()
	list( APPEND EXTERNAL_LIBS_LIBRARIES 	${VTK_LIBRARIES} ${QT_LIBRARIES} ${ITK_LIBRARIES} ${OPENGL_LIBRARIES})
endif()

# ------------------------------------------------------------------------------
# INCLUDE EXTERNAL LIBS
# ------------------------------------------------------------------------------
include_directories( ${EXTERNAL_LIBS_INCLUDE_DIR} )
