cmake_minimum_required(VERSION 3.7)
project(2inside C)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_LIBRARY_ttf /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
set(SDL2_LIBRARY_image /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
set(SDL2_LIBRARY_mixer /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so)
include_directories(src/hdr)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..
        )

add_executable(2inside
	src/ai.c        
	src/camera.c
        src/core.c
	src/ennemy.c
	src/entity.c
        src/graphics.c
        src/gui.c
	src/init.c
        src/input.c
        src/main.c
        src/map.c
	src/projectile.c
	src/sound.c
	src/spawner.c
        src/text.c
        src/texture.c
	src/hdr/ai.h        
	src/hdr/camera.h
        src/hdr/core.h
	src/hdr/define.h
	src/hdr/ennemy.h
	src/hdr/entity.h
        src/hdr/graphics.h
        src/hdr/gui.h
	src/hdr/init.h
        src/hdr/input.h
        src/hdr/map.h
	src/hdr/projectile.h
	src/hdr/sound.h
	src/hdr/spawner.h
        src/hdr/struct.h
        src/hdr/text.h
        src/hdr/texture.h)

target_link_libraries(2inside
        ${SDL2_LIBRARY}
        ${SDL2_LIBRARY_image}
        ${SDL2_LIBRARY_ttf}
	${SDL2_LIBRARY_mixer}
        m)
