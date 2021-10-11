FetchContent_Declare(
    zlib
    GIT_REPOSITORY  https://github.com/madler/zlib.git
    GIT_TAG         v1.2.11
)

FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
    FetchContent_Populate(zlib)

    add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})

    # Setting ZLIB_INCLUDE_DIR (to include header files), ZLIB_LIBRARY (to link it with our project) and ZLIB_DLL (to put together with executable, as we are building shared lib) paths
    # God knows why, but zlibd is not a Debug version, but a lib built with MSVC.
    set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} CACHE INTERNAL "ZLIB_INCLUDE_DIR")
    if(MSVC)
        set(ZLIB_LIBRARY ${zlib_BINARY_DIR}/Debug/zlibd.lib CACHE INTERNAL "ZLIB_LIBRARY")
        set(ZLIB_DLL ${zlib_BINARY_DIR}/Debug/zlibd.dll CACHE INTERNAL "ZLIB_DLL")
    elseif(UNIX)
        set(ZLIB_LIBRARY ${zlib_BINARY_DIR}/libz.so CACHE INTERNAL "ZLIB_LIBRARY")
        set(ZLIB_DLL ${zlib_BINARY_DIR}/libz.so CACHE INTERNAL "ZLIB_DLL")
    else()
        set(ZLIB_LIBRARY ${zlib_BINARY_DIR}/libzlib.dll.a CACHE INTERNAL "ZLIB_LIBRARY")
        set(ZLIB_DLL ${zlib_BINARY_DIR}/libzlib.dll CACHE INTERNAL "ZLIB_DLL")
    endif()

    # Noticed that when those test executables are built with MinGW, they don't have zlib source directory included, which leads to annoying building errors
    # Unfortunately there is just no option to disable their compilation
    if(NOT MSVC)
        target_include_directories(minigzip PUBLIC ${zlib_SOURCE_DIR})
        target_include_directories(minigzip64 PUBLIC ${zlib_SOURCE_DIR})
        target_include_directories(example PUBLIC ${zlib_SOURCE_DIR})
        target_include_directories(example64 PUBLIC ${zlib_SOURCE_DIR})
    endif()

    # zlib cmakelist has an annoying chunk of code, removing zconf.h because it is built in a different directory. That results in compilation errors
    # We fix it by moving zconf.h from build to source directory
    configure_file("${zlib_BINARY_DIR}/zconf.h" "${zlib_SOURCE_DIR}/zconf.h" COPYONLY)
endif()

# Adding dependencies to project, so it would be built as the last one
add_dependencies(${PROJECT_NAME} zlib)