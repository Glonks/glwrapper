set(target texture2D)

set(sources
	${target}.cpp
)

add_executable(${target}
	${sources}
)

target_link_libraries(${target}
	glwrapper
	glfw
)