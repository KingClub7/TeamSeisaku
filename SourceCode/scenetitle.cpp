#include"all.h"
void SceneTitle::render()
{
	GameLib::clear(0, 0, 0);
	GameLib::text_out(0, "THIS IS GAME", 1280/2, 720/2, 3, 3,1,1,1,1,TEXT_ALIGN::MIDDLE);
}
void SceneTitle::update()
{
	if (STATE(0) & PAD_START)
	{
		setScene(SCENE_GAME);
	}
}