FetchContent_Declare(
    libpng
    GIT_REPOSITORY  https://github.com/glennrp/libpng.git
    GIT_TAG         v1.6.35
)

FetchContent_GetProperties(libpng)
if(NOT libpng_POPULATED)
    FetchContent_Populate(libpng)

    set(PNG_BUILD_ZLIB ON CACHE INTERNAL "Custom zlib Location, else find_package is used")
    set(PNG_SHARED ON CACHE INTERNAL "Build shared lib")
    set(PNG_STATIC OFF CACHE INTERNAL "Build static lib")
    set(PNG_EXECUTABLES OFF CACHE INTERNAL "Build libpng executables")
    set(PNG_TESTS OFF CACHE INTERNAL "Build libpng tests")

    add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})

    # All libpng targets depend on zlib; as we are building zlib together with libpng, we need to explicitly add zlib as dependency to it, so zlib would be built before those targets
    add_dependencies(png zlib)
    add_dependencies(pngfix zlib)
    add_dependencies(png-fix-itxt zlib)

    # If libpng is built as Debug lib, it has 'd' appended to its name
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        set(PNG_NAME "png16d")
    else()
        set(PNG_NAME "png16")
    endif()

    # Setting PNG_INCLUDE_DIR (to include header files), PNG_LIBRARY (to link it with our project) and PNG_DLL (to put together with executable, as we are building shared lib) paths
    set(PNG_INCLUDE_DIR ${libpng_SOURCE_DIR} CACHE INTERNAL "PNG_INCLUDE_DIR")
    if(MSVC)
        set(PNG_LIBRARY ${libpng_BINARY_DIR}/Debug/lib${PNG_NAME}.lib CACHE INTERNAL "PNG_LIBRARY")
        set(PNG_DLL ${libpng_BINARY_DIR}/Debug/lib${PNG_NAME}.dll CACHE INTERNAL "PNG_DLL")
    elseif(UNIX)
        set(PNG_LIBRARY ${libpng_BINARY_DIR}/lib${PNG_NAME}.so CACHE INTERNAL "PNG_LIBRARY")
        set(PNG_DLL ${libpng_BINARY_DIR}/lib${PNG_NAME}.so CACHE INTERNAL "PNG_DLL")
    else()
        set(PNG_LIBRARY ${libpng_BINARY_DIR}/lib${PNG_NAME}.dll.a CACHE INTERNAL "PNG_LIBRARY")
        set(PNG_DLL ${libpng_BINARY_DIR}/lib${PNG_NAME}.dll CACHE INTERNAL "PNG_DLL")
    endif()
    
    # Because pnglibconf.h in the build directory is only generated during build, we are forced to use the pre-generated one
    configure_file("pnglibconf.h" "${libpng_SOURCE_DIR}/pnglibconf.h" COPYONLY)
endif()

# Adding dependencies to project, so it would be built as the last one
add_dependencies(${PROJECT_NAME} png)