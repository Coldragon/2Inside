cmake_minimum_required(VERSION 3.11)
project(2inside C)

set (CMAKE_C_STANDARD 99)

if (WIN32)
    if (MSVC)
        set(DEPENDENCIES_PATH "${CMAKE_SOURCE_DIR}/dependencies/msvc")
    else()
        set(DEPENDENCIES_PATH "${CMAKE_SOURCE_DIR}/dependencies/mingw")
    endif()
elseif (APPLE)
    set(DEPENDENCIES_PATH "${CMAKE_SOURCE_DIR}/dependencies/macos")
elseif (UNIX)
    set(DEPENDENCIES_PATH "${CMAKE_SOURCE_DIR}/dependencies/linux")
endif()

if (DEFINED DEPENDENCIES_PATH)
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2")
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2_ttf")
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2_image")
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/SDL2_mixer")
endif()

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

include_directories(src/hdr)
file(GLOB SRC_FILES src/*.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
add_executable(2inside ${SRC_FILES})

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

# Copy the res folder to the build directory
add_custom_command(TARGET 2inside POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res"
)

if (WIN32)
    # Copy SDL .dll files to the build directory
    add_custom_command(TARGET 2inside POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2_image::SDL2_image>
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2_mixer::SDL2_mixer>
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2_ttf::SDL2_ttf>
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )
endif()
