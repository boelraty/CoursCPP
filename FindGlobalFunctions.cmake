# Declare useful functions

###---------------------### 
### ---- FUNCTIONS ---- ###
###---------------------###

# ------------------------------------------------------------------------------
# Grouping
# ------------------------------------------------------------------------------
function( source_group_perso DIR GROUPNAME ) # + input list
    foreach( file ${ARGN} )
		string( REPLACE "${DIR}/" "" group_name ${file} ) 				# Remove dir
        string( REGEX REPLACE "/?[^/]+$" "" group_name ${group_name} ) 	# Remove filename
        string( REPLACE / \\ group_name "${GROUPNAME}/${group_name}" )	# Replace slashes by antislashes
        source_group( ${group_name} FILES ${file} )						# Source group
    endforeach()
endfunction()

# For headers
macro( source_group_headers ) # + input list
	source_group_perso( ${CMAKE_CURRENT_SOURCE_DIR} "Header Files" ${ARGV} )
endmacro()
# For sources
macro( source_group_sources ) # + input list
    source_group_perso( ${CMAKE_CURRENT_SOURCE_DIR} "Source Files" ${ARGV} )
endmacro()
# For mocs
macro( source_group_mocs ) # + input list
    source_group_perso( ${CMAKE_CURRENT_BINARY_DIR} "Generated Files" ${ARGV} )
endmacro()
# For qrcs
macro( source_group_qrcs ) # + input list
    source_group_perso( ${CMAKE_CURRENT_SOURCE_DIR} "QRC Files" ${ARGV} )
endmacro()
# For generated qrcs
macro( source_group_generated_qrcs ) # + input list
    source_group_perso( ${CMAKE_CURRENT_BINARY_DIR} "Generated Files" ${ARGV} )
endmacro()


# ------------------------------------------------------------------------------
# Qt
# ------------------------------------------------------------------------------
function( find_moc_files OUTPUT_VAR ) # + input list
    set( moc_list )
    foreach( file ${ARGN} )
        file( READ ${file} stream )					# read file
        if( stream MATCHES "Q_OBJECT" ) 			# look for Q_OBJECT
            list( APPEND moc_list ${file} ) 		# append file to tmp list
        endif()
    endforeach()
    set( ${OUTPUT_VAR} ${moc_list} PARENT_SCOPE ) 	# set output
endfunction()


#-----------------------------------------------------------
# Hpp files to header only
#-----------------------------------------------------------
function( manage_hpp_files ) # + input list
	foreach( file ${ARGN} )
		set_source_files_properties( ${file} PROPERTIES HEADER_FILE_ONLY 1 )
	endforeach()
endfunction()
