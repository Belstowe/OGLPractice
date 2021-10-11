include(FetchContent)

# 3.13 is a minimum version due to using 'target_link_libraries' instruction
cmake_minimum_required(VERSION 3.13..3.21)

project(
	OGLPractice
	VERSION 0.1.9
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

# I am too lazy to add source and header files one by one, let GLOB_RECURSE deal with it.
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

find_package(OpenGL REQUIRED)

include_directories(
        "${CMAKE_SOURCE_DIR}/src"
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

add_subdirectory(extras)

# MSVC has its own libm realization, not requiring to link it
if(NOT MSVC)
        set(LIBS ${LIBS} m)
endif()
# If it is Unix, when graphically it uses X11 Window System. Linking its libs to the project
# We don't check for it as GLFW dependency already does that for us
if(UNIX)
        set(LIBS ${LIBS} dl Xrandr Xrender Xi Xfixes Xxf86vm Xext X11 pthread xcb Xau Xdmcp)
        target_link_options(${PROJECT_NAME} BEFORE PRIVATE -Wl,--start-group)
endif()
set(LIBS ${LIBS} OpenGL::GL ${GLEW_LIBRARY} ${GLFW3_LIBRARY} ${ZLIB_LIBRARY} ${PNG_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE "${OPENGL_INCLUDE_DIR}" "${GLEW_INCLUDE_DIR}" "${GLM_INCLUDE_DIR}" "${GLFW3_INCLUDE_DIR}" "${PNG_INCLUDE_DIR}")

# Copying DLLs and resources (such as shaders and textures) to project binary file directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
                   COMMAND ${CMAKE_COMMAND} -E copy "${ZLIB_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
                   COMMAND ${CMAKE_COMMAND} -E copy "${PNG_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/res/" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/")