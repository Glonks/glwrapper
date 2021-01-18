set(target glwrapper)

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
	${include_path}/base/Assert.h
	${include_path}/base/Instantiator.h
	${include_path}/base/Source.h
	${include_path}/base/Log.h

	${include_path}/glwrapper.h
	${include_path}/StringSource.h
	${include_path}/FileSource.h
	${include_path}/Shader.h
	${include_path}/Program.h
	${include_path}/Buffer.h
	${include_path}/VertexArray.h
	${include_path}/VertexBindingPoint.h
	${include_path}/Texture.h
	${include_path}/Sampler.h
	${include_path}/FrameBuffer.h
)

set(sources
	${source_path}/base/Source.cpp
	${source_path}/base/Log.cpp

	${source_path}/StringSource.cpp
	${source_path}/FileSource.cpp
	${source_path}/Shader.cpp
	${source_path}/Program.cpp
	${source_path}/Buffer.cpp
	${source_path}/VertexArray.cpp
	${source_path}/VertexBindingPoint.cpp
	${source_path}/Texture.cpp
	${source_path}/Sampler.cpp
	${source_path}/FrameBuffer.cpp
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
		stb
		spdlog
)