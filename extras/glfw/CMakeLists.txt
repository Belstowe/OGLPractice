FetchContent_Declare(
    glfw3
    GIT_REPOSITORY  https://github.com/glfw/glfw.git
    GIT_TAG         3.3.4
)

FetchContent_GetProperties(glfw3)
if(NOT glfw3_POPULATED)
    FetchContent_Populate(glfw3)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw3_SOURCE_DIR} ${glfw3_BINARY_DIR})
    set(GLFW3_INCLUDE_DIR ${glfw3_SOURCE_DIR}/include CACHE INTERNAL "GLFW3_INCLUDE_DIR")
    if(MSVC)
        set(GLFW3_LIBRARY ${glfw3_BINARY_DIR}/src/Debug/glfw3.lib CACHE INTERNAL "GLFW3_LIBRARY")
    else()
        set(GLFW3_LIBRARY ${glfw3_BINARY_DIR}/src/libglfw3.a CACHE INTERNAL "GLFW3_LIBRARY")
    endif()
endif()

#add_dependencies(${PROJECT_NAME} glfw3)