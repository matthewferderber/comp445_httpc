cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall")
project(a1_40010150 C)

add_library(httpc_core SHARED
	src/help.h 
	src/help.c
	src/options.h
	src/get.h
	src/get.c 
	src/request.c 
	src/request.h
	src/url.h
	src/url.c
	src/util.h
	src/util.c
	src/types.h
    src/post.h
    src/post.c)

add_executable(httpc 
	src/main.c)

add_executable(httpc_tests
	src/tests.c)

target_link_libraries(httpc httpc_core)
target_link_libraries(httpc_tests httpc_core)
