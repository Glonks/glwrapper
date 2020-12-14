set(target square)

set(sources
	square.cpp
)

add_executable(${target}
	${sources}
)

target_link_libraries(${target}
	glwrapper
	glfw
)