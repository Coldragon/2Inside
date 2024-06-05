cmake_minimum_required(VERSION 3.7)
project(2inside C)

# Set the path to the SDL2 cmake folder
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/dependencies/SDL2")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/dependencies/SDL2_ttf")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/dependencies/SDL2_image")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/dependencies/SDL2_mixer")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

include_directories(src/hdr)
file(GLOB SRC_FILES src/*.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
add_executable(2inside ${SRC_FILES})

target_link_libraries(2inside
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)

# Copy the res folder to the build directory
add_custom_command(TARGET 2inside POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res"
)

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