#include"all.h"
OBJ2D Game_Over;
void GameOver::init()
{
	music::play(M_GAME_OVER,false);
	Game_Over.timer = 0;
	Game_Over.state = 0;
}
void GameOver::update()
{
	switch (Game_Over.state)
	{
	case 0:
		Game_Over.spr = sprite_load(L"./Data/Images/GameOver.png");
		Game_Over.animeno = 0;
		Game_Over.state++;
		break;
	case 1:
		if (Game_Over.timer % 10 == 0)
		{
			Game_Over.animeno++;
			if (Game_Over.animeno > 7)
				Game_Over.animeno = 0;
		}
		if (TRG(0) & PAD_START)
		{
			music::stop(M_GAME_OVER);
			setScene(SCENE_TITLE);
		}
		break;
	}
	Game_Over.timer++;
}
void GameOver::render()
{
	GameLib::clear(0, 0, 0);
	sprite_render(Game_Over.spr, 0, 0, 1, 1, 1280 * Game_Over.animeno, 0, 1280, 720);
}
void GameOver::deinit()
{
	safe_delete(Game_Over.spr);

}