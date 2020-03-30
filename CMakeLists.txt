cmake_minimum_required(VERSION 3.10)
project(JQR VERSION 1.0)
include_directories(inc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_BUILD_TYPE Debug)

set(TEST_PRG
	src/encode.c
)

set(QUE
	src/list.c
	src/que.c
	src/util.c
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

set(SERIAL
	src/encode.c
	src/util.c
)

set(SORT
	src/util.c
	src/sort.c
	src/list.c
)

set(linkedList
	src/list.c
	src/sort.c
	src/util.c
)

set(STACK
	src/util.c
	src/list.c
	src/sort.c
	src/stack.c
)

set(GRAPH
	src/graph.c
	${STACK}
	${QUE}
	src/util.c
)

set(DIJKSTRA
	${linkedList}
	${GRAPH}
	src/util.c
)
	
#3-1 Executables
add_executable(04 "3-1/04.c")
add_executable(05 "3-1/05.c")
add_executable(06 "3-1/06.c")
add_executable(07 "3-1/07.c")
add_executable(08 "3-1/08.c")
add_executable(09 "3-1/09.c")
add_executable(10 "3-1/10.c")
add_executable(11 "3-1/11.c")
add_executable(server "3-1/12_server.c")
add_executable(client "3-1/12_client.c")
add_executable(talker "3-1/12_talker.c")
add_executable(listener "3-1/12_listener.c")
add_executable(serial_send "3-1/12_serial_send.c" ${SERIAL})
add_executable(serial_recv "3-1/12_serial_recv.c" ${SERIAL})
#add_executable(hash "3-1/13.c" ${HASH})
add_executable(sort "3-1/14.c" ${SORT})
add_executable(15 "3-1/15.c")
add_executable(dijkstra "3-1/dijkstra.c" ${DIJKSTRA})
add_executable(21 "3-1/21.c")

#3-3 Executables
add_executable(linkedList "3-3/linkedList.c" ${linkedList})
add_executable(que "3-3/queTest.c" ${QUE})
add_executable(stack "3-3/stackTest.c" ${STACK})
#add_executable(tree "3-3/treeTest.c" ${TREE})
add_executable(graph "3-3/graphTest.c" ${GRAPH})

