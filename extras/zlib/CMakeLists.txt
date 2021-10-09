FetchContent_Declare(
    zlib
    GIT_REPOSITORY  https://github.com/madler/zlib.git
    GIT_TAG         v1.2.11
)

FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
    FetchContent_Populate(zlib)

    add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
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

    set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} CACHE INTERNAL "ZLIB_INCLUDE_DIR")

    if(NOT MSVC)
        target_include_directories(minigzip PUBLIC ${zlib_SOURCE_DIR})
        target_include_directories(minigzip64 PUBLIC ${zlib_SOURCE_DIR})
        target_include_directories(example PUBLIC ${zlib_SOURCE_DIR})
        target_include_directories(example64 PUBLIC ${zlib_SOURCE_DIR})
    endif()

    configure_file("${zlib_BINARY_DIR}/zconf.h" "${zlib_SOURCE_DIR}/zconf.h" COPYONLY)
endif()

add_dependencies(${PROJECT_NAME} zlib)