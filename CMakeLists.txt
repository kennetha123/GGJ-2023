cmake_minimum_required(VERSION 3.17)

set(OutputFolderName project)
set(ProjectName 2DRPG)
set(ProjectFolder project/src)
set(CodeFolder code/src)

project(${ProjectName} VERSION 1.1)

file(MAKE_DIRECTORY ${OutputFolderName})

add_executable(${ProjectName} 
				${CodeFolder}/main.cpp
				${CodeFolder}/header.h.in)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OutputFolderName})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OutputFolderName})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OutputFolderName})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OutputFolderName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET ${ProjectName} PROPERTY FOLDER ${OutputFolderName})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${ProjectName})

configure_file(${CodeFolder}/header.h.in src/header.h)

link_directories(deps/SFML/libs)
include_directories(deps/SFML/include)

find_library(SFML_SYSTEM NAMES sfml-system-d.lib PATHS "deps/SFML/lib")
find_library(SFML_WINDOW NAMES sfml-window-d.lib PATHS "deps/SFML/lib")
find_library(SFML_GRAPHICS NAMES sfml-graphics-d.lib PATHS "deps/SFML/lib")
target_link_libraries(${ProjectName} ${SFML_SYSTEM} ${SFML_WINDOW} ${SFML_GRAPHICS})

set(SFML_DLL_FILES 
    sfml-graphics-d-2.dll 
    sfml-system-d-2.dll 
    sfml-window-d-2.dll)

foreach(SFML_DLL_FILE ${SFML_DLL_FILES})
    add_custom_command(TARGET ${ProjectName} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${CMAKE_CURRENT_SOURCE_DIR}/deps/SFML/dll/${SFML_DLL_FILE}
                       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/${SFML_DLL_FILE})
endforeach()