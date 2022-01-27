#pragma once
#include"scene.h"
class SceneRule :public Scene
{
	int state;
public:

	void init() { state = 0; }
	void update();
	void render();
	void deinit();
};
