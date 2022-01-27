#pragma once
#include"Scene.h"
class GameOver :public Scene
{
public:
	void init();
	void update();
	void render();
	void deinit();
};