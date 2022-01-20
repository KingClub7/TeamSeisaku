#pragma once
#include"scene.h"
class SceneTitle :public Scene
{
	int i=0;
public:
	
	void init() {};
	void update();
	void render();
	void deinit() {};
};