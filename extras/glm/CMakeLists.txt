FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         0.9.9.8
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    # GLM is only an interface library, so we need only header files from it
    add_library(glm INTERFACE)
    target_include_directories(glm INTERFACE ${glm_SOURCE_DIR})

    set(GLM_INCLUDE_DIR ${glm_SOURCE_DIR} CACHE INTERNAL "GLM_INCLUDE_DIR")
endif()

# Adding dependencies to project, so it would be built as the last one
add_dependencies(${PROJECT_NAME} glm)