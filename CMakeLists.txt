cmake_minimum_required(VERSION 3.10)
project(a1_40010150 C)

set(CMAKE_C_STANDARD 99)

add_executable(httpc 
	src/main.c 
	src/help.h 
	src/help.c
	src/options.h
	src/get.h
	src/get.c 
	src/request.c 
	src/request.h
	src/url.h
	src/url.c)
