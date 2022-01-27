#include"all.h"
Sprite* spr_Rule;
void SceneRule::update()
{
	switch (state)
	{
	case 0:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		spr_Rule = sprite_load(L"./Data/Images/Setsumei1.png");
		if (TRG(0) & PAD_START)
			state++;
		break;
	case 1:
		spr_Rule = sprite_load(L"./Data/Images/Setsumei2.png");
		if (TRG(0) & PAD_START)
			state++;
		break;
	case 2:
		spr_Rule = sprite_load(L"./Data/Images/Setsumei3.png");
		if (TRG(0) & PAD_START)
			setScene(SCENE_TITLE);
		break;
	}
}
void SceneRule::render()
{
	GameLib::clear(1,1,1);
	sprite_render(spr_Rule, 0, 0);
}
void SceneRule::deinit()
{
	safe_delete(spr_Rule);
}