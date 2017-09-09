#ifndef DEF_INIT
#define DEF_INIT
#include "camera.h"

void open_sdl_shit();
void close_sdl_shit();
void time_init(TIME *limiter);
void state_init(STATE *state);
void camera_init(CAMERA *camera);
void map_init(MAP *map);
void core_init(CORE *game);

#endif
