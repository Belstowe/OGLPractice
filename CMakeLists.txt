include(FetchContent)

cmake_minimum_required(VERSION 3.11..3.21)

project(
	OGLPractice
	VERSION 0.1.9
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h)

find_package(OpenGL REQUIRED)

include_directories(
        "${CMAKE_SOURCE_DIR}/src"
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

add_subdirectory(extras)

if(NOT MSVC)
        set(LIBS ${LIBS} m)
endif()
if(UNIX)
        set(LIBS ${LIBS} dl Xrandr Xrender Xi Xfixes Xxf86vm Xext X11 pthread xcb Xau Xdmcp)
        target_link_options(${PROJECT_NAME} BEFORE PRIVATE -Wl,--start-group)
endif()
set(LIBS ${LIBS} OpenGL::GL ${GLEW_LIBRARY} ${GLFW3_LIBRARY} ${ZLIB_LIBRARY} ${PNG_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE "${OPENGL_INCLUDE_DIR}" "${GLEW_INCLUDE_DIR}" "${GLM_INCLUDE_DIR}" "${GLFW3_INCLUDE_DIR}" "${PNG_INCLUDE_DIR}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
                   COMMAND ${CMAKE_COMMAND} -E copy "${ZLIB_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
                   COMMAND ${CMAKE_COMMAND} -E copy "${PNG_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/res/" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/")