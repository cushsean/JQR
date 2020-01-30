cmake_minimum_required(VERSION 3.10)
project(JQR VERSION 1.0)
include_directories(inc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_BUILD_TYPE Debug)

set(QUE
	src/list.c
	src/que.c
)

set(TREE
	src/list.c
	src/tree.c
	src/util.c
)

set(HASH
	src/hash.c
	src/list.c
	src/util.c
)
	
add_executable(02 "3-3/02.c")
add_executable(03 "3-3/03.c")
add_executable(04 "3-3/04.c")
add_executable(05 "3-3/05.c" ${QUE})
add_executable(07 "3-3/07.c" ${TREE})
add_executable(hash "3-1/13.c" ${HASH})
