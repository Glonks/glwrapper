set(target texture2D)

set(sources
	texture2D.cpp
)

add_executable(${target}
	${sources}
)

target_link_libraries(${target}
	glwrapper
	glfw
)