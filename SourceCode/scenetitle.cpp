#include"all.h"
OBJ2D title;
OBJ2D Present;
Sprite* sprRule;
Sprite* sprGameStart;
int choose;
void choose_update();
void SceneTitle::init()
{
	music::play(M_GAME_TITLE, true);
	title.timer = 0;
	title.state = 0;
}
void SceneTitle::update()
{
	
	switch (title.state)
	{
	case 0:
		
		GameLib::setBlendMode(Blender::BS_ALPHA);
		title.spr = sprite_load(L"./Data/Images/back.png");
		Present.spr = sprite_load(L"./Data/Images/Title.png");
		sprGameStart = sprite_load(L"./Data/Images/icon1.png");
		sprRule = sprite_load(L"./Data/Images/icon2.png");
		Present.animeno = 0;
		title.animeno = 0;
		choose = 505;
		title.state++;
		break;
	case 1:
		
		
		if (title.timer % 10 == 0)
		{
			Present.animeno++;
			title.animeno++;
			if (title.animeno > 4)
				title.animeno = 0;
			if (Present.animeno > 5)
				Present.animeno = 0;
		}
		choose_update();
		break;
	}
	title.timer++;
}
void choose_update()
{

	switch (TRG(0)&(PAD_UP|PAD_DOWN))
	{
	case PAD_UP:
		
		choose = 505;
		break;
	case PAD_DOWN:
		
		choose = 605;
		break;
	default:
		break;
	}
	if (TRG(0) & PAD_START)
	{
		if (choose == 505)
		{
			sound::play(SOUND, SOUND_SELECT);
			music::stop(M_GAME_TITLE);
			setScene(SCENE_GAME);
			return;
			
		}
			
		if (choose == 605)
		{
			sound::play(SOUND, SOUND_SELECT);
			setScene(SCENE_RULE);
			return;
		}
			
	}
}
void SceneTitle::render()
{
	GameLib::clear(0, 0, 0);
	sprite_render(title.spr, 0, 0, 1, 1, 1280 * title.animeno, 0, 1280, 720);
	sprite_render(Present.spr, 640, 200, 1, 1, 700 * Present.animeno, 0, 700, 398,350,199);
	sprite_render(sprGameStart, 640, 500, 1, 1, 0,0,300,80,150,40);
	sprite_render(sprRule, 640, 600, 1, 1, 0, 0, 300, 80,150,40);
	sprite_render(Present.spr, 430, choose, 0.2, 0.2, 263+700 * title.animeno, 160, 174, 300,87,150);

}
void SceneTitle::deinit()
{
	safe_delete(title.spr);
	safe_delete(Present.spr);
	safe_delete(sprGameStart);
	safe_delete(sprRule);

}