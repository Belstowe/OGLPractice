FetchContent_Declare(
    glew
    GIT_REPOSITORY  https://github.com/Perlmint/glew-cmake.git
    GIT_TAG         ce3818d22f1efa6b8d7517fb928c1c33d23ff58c
)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_Populate(glew)

    set(glew-cmake_BUILD_SHARED ON CACHE INTERNAL "Build the shared glew library")
    set(glew-cmake_BUILD_STATIC OFF CACHE INTERNAL "Build the static glew library")
    set(ONLY_LIBS ON CACHE INTERNAL "Do not build executables")

    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})

    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        set(GLEW_NAME "glewd")
    else()
        set(GLEW_NAME "glew")
    endif()

    set(GLEW_INCLUDE_DIR ${glew_SOURCE_DIR}/include CACHE INTERNAL "GLEW_INCLUDE_DIR")
    if(MSVC)
        set(GLEW_LIBRARY ${glew_BINARY_DIR}/lib/Debug/${GLEW_NAME}.lib CACHE INTERNAL "GLEW_LIBRARY")
        set(GLEW_DLL ${glew_BINARY_DIR}/bin/Debug/${GLEW_NAME}.dll CACHE INTERNAL "GLEW_DLL")
    elseif(UNIX)
        set(GLEW_LIBRARY ${glew_BINARY_DIR}/lib/lib${GLEW_NAME}.so CACHE INTERNAL "GLEW_LIBRARY")
        set(GLEW_DLL ${glew_BINARY_DIR}/lib/lib${GLEW_NAME}.so CACHE INTERNAL "GLEW_DLL")
    else()
        set(GLEW_LIBRARY ${glew_BINARY_DIR}/lib/lib${GLEW_NAME}.dll.a CACHE INTERNAL "GLEW_LIBRARY")
        set(GLEW_DLL ${glew_BINARY_DIR}/bin/lib${GLEW_NAME}.dll CACHE INTERNAL "GLEW_DLL")
    endif()
endif()

add_dependencies(${PROJECT_NAME} libglew_shared)