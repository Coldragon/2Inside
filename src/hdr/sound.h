#ifndef DEF_SOUND
#define DEF_SOUND
#include "struct.h"

void init_soundsystem(SOUNDSYSTEM *soundsystem);
void music_load(SOUNDSYSTEM *soundsystem, char path[]);
void music_control(SOUNDSYSTEM *soundsystem, int control);
void music_volume(SOUNDSYSTEM *soundsystem, int volume);
void chunk_load(SOUNDSYSTEM *soundsystem, char path[]);
void chunk_play(SOUNDSYSTEM *soundsystem, int nb, int volume);

#endif