#include"all.h"
void SceneClear::init()
{
	music::play(M_GAME_CLEAR,false);
	state = 0;
	timer = 0;
	animeno = 0;
}
void SceneClear::update()
{
	switch (state)
	{
	case 0:
		clear=sprite_load(L"./Data/Images/clear.png");
		state++;
	case 1:
		if (timer % 10 == 0)
		{
			animeno++;
			if (animeno > 3)
				animeno = 0;
		}
		if (TRG(0) & PAD_START)
		{
			music::stop(M_GAME_CLEAR);
			setScene(SCENE_TITLE);
		}
			
		break;
		
	}
	timer++;
}
void SceneClear::render()
{
	GameLib::clear(0, 0, 0);
	sprite_render(clear, 0, 0, 1, 1, 1280*animeno, 0, 1280, 720);
}
void SceneClear::deinit()
{
	safe_delete(clear);
}