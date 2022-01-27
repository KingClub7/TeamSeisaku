#pragma once
#include"../GameLib/game_lib.h"
using namespace GameLib;
using namespace input;
class Scene
{
public:
	virtual void init() {}
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void deinit() = 0;
};