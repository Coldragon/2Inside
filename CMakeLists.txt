cmake_minimum_required(VERSION 3.7)
project(Terminal C)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_LIBRARY_ttf /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
set(SDL2_LIBRARY_image /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
include_directories(src/hdr)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..
        )

add_executable(Terminal
        src/camera.c
        src/core.c
        src/graphics.c
        src/gui.c
        src/input.c
        src/main.c
        src/map.c
        src/text.c
        src/texture.c
        src/hdr/camera.h
        src/hdr/core.h
        src/hdr/graphics.h
        src/hdr/gui.h
        src/hdr/input.h
        src/hdr/map.h
        src/hdr/struct.h
        src/hdr/text.h
        src/hdr/texture.h)

target_link_libraries(Terminal
        ${SDL2_LIBRARY}
        ${SDL2_LIBRARY_image}
        ${SDL2_LIBRARY_ttf}
        m)
