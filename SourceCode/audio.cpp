#include"all.h"
void audio_init()
{
	music::load(M_GAME_TITLE, L"./Data/Musics/Title.wav");
	music::load(M_GAME_CLEAR, L"./Data/Musics/gameclear.wav");
	music::load(M_GAME_OVER, L"./Data/Musics/GameOver.wav");
	music::load(M_GAME_BATTLE	, L"./Data/Musics/Battle.wav");
	sound::load(SOUND, L"./Data/Musics/SE/SE.xwb");
	sound::setVolume(SOUND, SOUND_SELECT, 0.3f);
	sound::setVolume(SOUND, SOUND_BOMB, 0.3f);
	sound::setVolume(SOUND, SOUND_HITPLAYER, 0.3f);
	sound::setVolume(SOUND, SOUND_HITENEMY, 0.3f);
	sound::setVolume(SOUND, SOUND_SHOT, 0.3f);
}
void audio_deinit()
{
	music::clear();
}