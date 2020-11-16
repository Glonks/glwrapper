set(target glwrapper)

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers

)

set(sources

)

add_library(${target}
	${headers}
	${sources}
)

target_include_directories(${target}
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include

	PRIVATE
)

target_link_libraries(${target}
	PUBLIC
)
