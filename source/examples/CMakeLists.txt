set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# simple triangle
add_subdirectory(triangle)

# square
add_subdirectory(square)

# 2D texture
add_subdirectory(texture2D)