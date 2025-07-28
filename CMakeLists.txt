cmake_minimum_required(VERSION 3.21)

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

if(UNIX)
    InterfaceImport("dmuuid" "include" "uuid")
else(UNIX)
    InterfaceImport("dmuuid" "include" "")
endif(UNIX)

if (PROJECT_IS_TOP_LEVEL)
    IF (WIN32)
        ExeImport("test" "dmtest")
    ELSEIF (APPLE)
        ExeImport("test" "dmtest")
    ELSE(UNIX)
        ExeImport("test" "dmtest")
    ENDIF(WIN32)
endif ()
