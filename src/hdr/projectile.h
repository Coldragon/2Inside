#ifndef DEF_PROJECTILE
#define DEF_PROJECTILE

void create_projectile(PROJECTILESYSTEM *projectilesystem, ENTITY origin, int x_dest, int y_dest, int texture_index);
void afficher_projectile(CORE *game);
void move_projectile(CORE *game);
void destroy_projectile();

#endif