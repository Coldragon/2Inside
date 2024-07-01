cmake_minimum_required(VERSION 3.11)
project(2inside C)

set (CMAKE_C_STANDARD 99)

# ===============================
# MARK: DEPENDENCIES BASE PATH
# ===============================
# Base path for dependencies
set(BASE_DEPENDENCIES_PATH "${CMAKE_SOURCE_DIR}/dependencies")

# Find the proper platform dependencies folder
if (WIN32 AND MSVC)
    set(DEPENDENCIES_PATH "${BASE_DEPENDENCIES_PATH}/msvc")
elseif (WIN32)
    set(DEPENDENCIES_PATH "${BASE_DEPENDENCIES_PATH}/mingw")
elseif (APPLE)
    set(DEPENDENCIES_PATH "${BASE_DEPENDENCIES_PATH}/macos")
endif()

if (DEFINED DEPENDENCIES_PATH)
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2")
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2_ttf")
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2_image")
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2_mixer")
endif()

# ===============================
# MARK: FIND LIBRARIES
# ===============================
if (APPLE)
    # Define SDL2 framework paths
    find_library(SDL2_LIB SDL2 PATHS "${DEPENDENCIES_PATH}/SDL2/SDL2.xcframework/macos-x86_64" NO_DEFAULT_PATH)
    find_library(SDL2_TTF_LIB SDL2_ttf PATHS "${DEPENDENCIES_PATH}/SDL2_ttf/SDL2_ttf.xcframework/macos-x86_64" NO_DEFAULT_PATH)
    find_library(SDL2_IMAGE_LIB SDL2_image PATHS "${DEPENDENCIES_PATH}/SDL2_image/SDL2_image.xcframework/macos-x86_64" NO_DEFAULT_PATH)
    find_library(SDL2_MIXER_LIB SDL2_mixer PATHS "${DEPENDENCIES_PATH}/SDL2_mixer/SDL2_mixer.xcframework/macos-x86_64" NO_DEFAULT_PATH)

    set(SDL2_LIBS ${SDL2_LIB} ${SDL2_TTF_LIB} ${SDL2_IMAGE_LIB} ${SDL2_MIXER_LIB})
else()
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)
    find_package(SDL2_mixer CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)
endif()

# ===============================
# MARK: SOURCES
# ===============================
# Include Headers & Sources to Executable
include_directories(src/hdr)
file(GLOB SRC_FILES src/*.c)
add_executable(2inside ${SRC_FILES})

# ===============================
# MARK: LINK LIBRARIES
# ===============================
if (APPLE)
    target_link_libraries(2inside PRIVATE ${SDL2_LIBS})
else()
    target_link_libraries(2inside
            PRIVATE
            $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
            $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
            $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
            $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
            $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    )
endif()

# ===============================
# MARK: SET OUTPUTS DIRECTORY
# ===============================
# Set output directory for Visual Studio
if (WIN32 AND MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
endif()

# ===============================
# MARK: RES FOLDER COPY
# ===============================
add_custom_command(
        TARGET 2inside POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:2inside>/res"
)

# ===============================
# MARK: WIN32 DDL COPY
# ===============================
if (WIN32)
    # Define SDL DLL paths based on architecture and compiler
    if (MSVC)
        if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
            # 32-bit MSVC
            set(SDL_DLL_PATH "${DEPENDENCIES_PATH}/SDL2/lib/x86")
            set(SDL_TTF_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_ttf/lib/x86")
            set(SDL_IMAGE_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_image/lib/x86")
            set(SDL_MIXER_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_mixer/lib/x86")
        elseif ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            # 64-bit MSVC
            set(SDL_DLL_PATH "${DEPENDENCIES_PATH}/SDL2/lib/x64")
            set(SDL_TTF_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_ttf/lib/x64")
            set(SDL_IMAGE_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_image/lib/x64")
            set(SDL_MIXER_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_mixer/lib/x64")
        endif()
    elseif (MINGW)
        if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
            # 32-bit MinGW
            set(SDL_DLL_PATH "${DEPENDENCIES_PATH}/SDL2/i686-w64-mingw32/bin")
            set(SDL_TTF_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_ttf/i686-w64-mingw32/bin")
            set(SDL_IMAGE_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_image/i686-w64-mingw32/bin")
            set(SDL_MIXER_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_mixer/i686-w64-mingw32/bin")
        elseif ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            # 64-bit MinGW
            set(SDL_DLL_PATH "${DEPENDENCIES_PATH}/SDL2/x86_64-w64-mingw32/bin")
            set(SDL_TTF_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_ttf/x86_64-w64-mingw32/bin")
            set(SDL_IMAGE_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_image/x86_64-w64-mingw32/bin")
            set(SDL_MIXER_DLL_PATH "${DEPENDENCIES_PATH}/SDL2_mixer/x86_64-w64-mingw32/bin")
        endif()
    endif()

    # Copy SDL DLL files to the build directory
    file(GLOB SDL_DLLS "${SDL_DLL_PATH}/*.dll"
            "${SDL_TTF_DLL_PATH}/*.dll"
            "${SDL_IMAGE_DLL_PATH}/*.dll"
            "${SDL_MIXER_DLL_PATH}/*.dll")

    foreach(SDL_DLL ${SDL_DLLS})
        add_custom_command(TARGET 2inside POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL_DLL} "$<TARGET_FILE_DIR:2inside>")
    endforeach()
endif()