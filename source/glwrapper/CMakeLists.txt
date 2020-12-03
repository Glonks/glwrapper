set(target glwrapper)

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
	${include_path}/base/Instantiator.h
	${include_path}/base/Source.h
	${include_path}/base/StringSource.h
	${include_path}/base/FileSource.h

	${include_path}/RenderingContext.h
	${include_path}/Shader.h
	${include_path}/Buffer.h

	${include_path}/opengl/GLShader.h
)

set(sources
	${source_path}/base/Source.cpp
	${source_path}/base/StringSource.cpp
	${source_path}/base/FileSource.cpp
	${source_path}/Shader.cpp

	${source_path}/opengl/GLShader.cpp
)

add_library(${target}
	${headers}
	${sources}
)

target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${target}
	PUBLIC
		glad
		glm
		stb_image
)