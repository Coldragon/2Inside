#ifndef DEF_ENTITY
#define DEF_ENTITY
#include "struct.h"

void create_entity(CORE *core, int x, int y, int speed, char* texturepath);
void draw_entity(CORE *game);
void move_entity(CORE *game);

#endif
