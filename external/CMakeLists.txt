# External libraries
set(IDE_FOLDER "external")

# Glad
add_subdirectory(glad)

# GLM
add_subdirectory(glm)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

# STB
add_subdirectory(stb)

# SPDLOG
add_subdirectory(spdlog)