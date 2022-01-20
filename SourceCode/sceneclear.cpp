#include"all.h"
void SceneClear::init()
{
	clear_timer = 300;
}
void SceneClear::update()
{
	clear_timer--;
	if (clear_timer < 0)
		setScene(SCENE_TITLE);
}
void SceneClear::render()
{
	GameLib::clear(0, 0, 0);
	GameLib::text_out(0, "TESTING", 300, 300, 2, 2);
}