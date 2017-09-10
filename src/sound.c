#include "hdr/sound.h"
#include <stdio.h>

void init_soundsystem(SOUNDSYSTEM *soundsystem)
{

	soundsystem->max_channel = 16;
	soundsystem->channel_to_use = 1;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
	Mix_AllocateChannels(16);
	Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG);

}

void music_load(SOUNDSYSTEM *soundsystem, char path[])
{
	soundsystem->music=Mix_LoadMUS(path);
}

void music_control(SOUNDSYSTEM *soundsystem, int control)
{
	if (control == 1)
	{
	Mix_PlayMusic(soundsystem->music, -1);
	}
	else if (control == 0 )
	{
	Mix_PauseMusic();
	}
	else if (control == -1)
	{
	Mix_ResumeMusic();
	}
}

void music_volume(SOUNDSYSTEM *soundsystem, int volume)
{
	Mix_VolumeMusic(volume);
}

void chunk_load(SOUNDSYSTEM *soundsystem, char path[])
{
	soundsystem->sound[soundsystem->tofill] = Mix_LoadWAV(path);
	if (!soundsystem->sound[soundsystem->tofill])
	{
		printf("Mix_LoadWAV(): %s\n", Mix_GetError());
	}

	soundsystem->tofill++;
	if (soundsystem->tofill >= 25)
		soundsystem->tofill = 0;
}

void chunk_play(SOUNDSYSTEM *soundsystem, int nb, int volume)
{
	Mix_Volume(soundsystem->channel_to_use, volume);
	Mix_PlayChannel(soundsystem->channel_to_use, soundsystem->sound[nb], 0);
	soundsystem->channel_to_use++;
	if (soundsystem->channel_to_use >= soundsystem->max_channel)
		soundsystem->channel_to_use = 0;
}