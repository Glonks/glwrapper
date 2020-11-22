set(target glad)

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
	${include_path}/glad/glad.h
	${include_path}/KHR/khrplatform.h
)

set(sources
	${source_path}/glad.c
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

set_target_properties(${target}
	PROPERTIES
		FOLDER ${IDE_FOLDER}
)
