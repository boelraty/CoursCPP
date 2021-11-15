cmake_minimum_required( VERSION 3.15 )


project( TestAppli )


if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

include(FindGlobalFunctions.cmake)
include(FindExternalLibs.cmake)


#-----------------------------------------------------------
# Create header/source/hpp/ui/qrc files list
#-----------------------------------------------------------
file( GLOB_RECURSE header_files *.h )
file( GLOB_RECURSE source_files *.cpp )



#-----------------------------------------------------------
# source_group
#-----------------------------------------------------------
source_group_sources( ${header_files} )
source_group_sources( ${source_files} )
source_group_sources( ${hpp_files} )


#-----------------------------------------------------------
# Include directories
#-----------------------------------------------------------
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )


#-----------------------------------------------------------
# Set hpp to header only
#-----------------------------------------------------------
manage_hpp_files( ${hpp_files} )


#-----------------------------------------------------------
# final link
#-----------------------------------------------------------
add_executable( ${PROJECT_NAME} ${header_files} ${source_files} ${hpp_files} )
target_link_libraries( ${PROJECT_NAME} ${MAIN_PROJECT_NAME} ${EXTERNAL_LIBS_LIBRARIES} )