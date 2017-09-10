#ifndef DEF_PROJECTILE
#define DEF_PROJECTILE

void create_projectile(PROJECTILESYSTEM *projectilesystem, ENTITY origin, int x_dest, int y_dest, int texture_index, int owner);
void afficher_projectile(CORE *game);
void move_projectile(CORE *game);
int distancepoint(int x1, int y1, int x2, int y2);
void destroy_projectile(CORE *game);

#endif