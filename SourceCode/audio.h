#ifndef AUDIO_H
#define AUDIO_H

#define M_GAME_TITLE	0
#define M_GAME_CLEAR	1
#define M_GAME_OVER		2
#define M_GAME_BATTLE	3
using namespace input;
#define SOUND 0

#define SOUND_SELECT	0
#define SOUND_BOMB		1
#define SOUND_HITPLAYER	2
#define SOUND_HITENEMY	3
#define SOUND_SHOT		4

void audio_init();
void audio_deinit();
#endif