cmake_minimum_required(VERSION 3.10)

project(JQR VERSION 1.0)
include_directories(inc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(SRC 
	src/tree.c
	src/list.c
	src/que.c
	src/util.c
)


add_executable(02 "3-3/02.c" ${SRC})
add_executable(03 "3-3/03.c" ${SRC})
add_executable(04 "3-3/04.c" ${SRC})
add_executable(05 "3-3/05.c" ${SRC})
add_executable(06 "3-3/06.c" ${SRC})
add_executable(07 "3-3/07.c" ${SRC})
