set(target imgui)

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
	${include_path}/imgui.h
	${include_path}/imgui_internal.h
	${include_path}/imstb_rectpack.h
	${include_path}/imstb_textedit.h
	${include_path}/imstb_truetype.h
	${include_path}/imconfig.h
	${include_path}/imgui_impl_glfw.h
	${include_path}/imgui_impl_opengl3.h
)

set(sources
	${source_path}/imgui.cpp
	${source_path}/imgui_draw.cpp
	${source_path}/imgui_impl_glfw.cpp
	${source_path}/imgui_impl_opengl3.cpp
	${source_path}/imgui_widgets.cpp
)

add_library(${target}
	STATIC
		${headers}
		${sources}
)

target_link_libraries(${target}
	PRIVATE
		glad
)

target_include_directories(${target}
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include

	PRIVATE
		${include_path}
)

target_compile_definitions(${target}
	PRIVATE
		IMGUI_IMPL_OPENGL_LOADER_GLAD=1
)

set_target_properties(${target}
	PROPERTIES
		FOLDER ${IDE_FOLDER}
)
