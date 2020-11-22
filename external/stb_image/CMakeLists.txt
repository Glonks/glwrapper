cmake_minimum_required(VERSION 3.16)
set(target stb_image)

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
	${include_path}/stb_image.h
)

set(sources
	${source_path}/stb_image.cpp
)

add_library(${target}
    STATIC
        ${headers}
        ${sources}
)

target_include_directories(${target}
    PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)