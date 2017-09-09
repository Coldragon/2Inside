#ifndef DEF_CAMERA
#define DEF_CAMERA
#include "core.h"

/// return a "real" position from a "virtual"
SDL_Rect position_to_screen(SDL_Rect rect, CAMERA *camera);

/// return a "virtual" position from a "real"
SDL_Rect screen_to_position(SDL_Rect rect, CAMERA *camera);

/// Multipli R by game.time.delta to move from R per SECONDS and not per Frames
void move_position_r(float *x1, float *y1, float x2, float y2, float r);
void move_from_angle(float *x, float *y, double angle, float r);

double angle_calculate_degree(float x1, float y1, float x2, float y2);
double angle_calculate_radiant(float x1, float y1, float x2, float y2);

void camera_move(CORE *game);
void camera_zoom(CORE *game);
void camera_space(CORE *game);

#endif
