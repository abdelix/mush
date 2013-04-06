cmake_minimum_required(VERSION 2.8)

project(mush)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_SOURCE_DIR}/config.h")

link_directories (${PROJECT_BINARY_DIR}/src) 
include_directories("${PROJECT_SOURCE_DIR}/include")


add_executable(mush main.c)

#añadir directorios
add_subdirectory(include)
add_subdirectory(src)


#librerias adicionales
target_link_libraries (mush parser readline commands builtin)






