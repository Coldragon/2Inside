#ifndef DEF_ENTITY
#define DEF_ENTITY
#include "struct.h"

void create_entity(CORE *game, int x, int y, int speed, int identity, char* texturepath);
void draw_entity(CORE *game);
void move_entity(CORE *game);
void destroy_entity(CORE *game);

#endif
