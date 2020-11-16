set(IDE_FOLDER "")
add_subdirectory(glwrapper)

if(GLWRAPPER_BUILD_EXAMPLES)
	set(IDE_FOLDER "examples")
	add_subdirectory(examples)
endif()
