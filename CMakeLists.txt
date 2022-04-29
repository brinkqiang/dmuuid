cmake_minimum_required(VERSION 3.2)

PROJECT(dmuuid)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

SET(DMUUID_VERSION_MAJOR "1")
SET(DMUUID_VERSION_MINOR "0")
SET(DMUUID_VERSION_PATCH "1")
SET(DMUUID_VERSION "${DMUUID_VERSION_MAJOR}.${DMUUID_VERSION_MINOR}.${DMUUID_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMUUID_VERSION}")

OPTION(USE_DMUUID "use dmuuid" OFF)

ModuleImportAll("thirdparty")

IF (WIN32)
    ExeImport("test" "")
ELSEIF (APPLE)
    ExeImport("test" "")
ELSE(UNIX)
    ExeImport("test" "uuid")
ENDIF(WIN32)


#ADD_CUSTOM_COMMAND(
#TARGET dmuuidtest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmuuidtest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmuuid
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMUUID_LIBS "dmuuid")
#MARK_AS_ADVANCED(${DMUUID_LIBS})
