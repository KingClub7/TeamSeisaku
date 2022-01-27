#include"all.h"
OBJ2D::OBJ2D()
{
	pos = { 0,0 };
	speed = { 0,0 };
	texpos = { 0,0 };
	texHW = { 0,0 };
	texprivot = { 0,0 };
	HW = { 0,0 };
	state = 0;
	jumpcount = 2;
	bombcount = 5;
	timer = 0;
	size = { 1,1 };
	spr = nullptr;
	animeno = 0;
	alpha = 1;
	effectTimer = 60;
}
void OBJ2D::bomb_init(OBJ2D* obj)
{
	obj->spr = sprite_load(L"./Data/Images/countBom2.png");
	obj->animeno = 0;
	obj->timer = 0;
	obj->state = 0;
	obj->pos = { static_cast<float>(rand()%1081+100),720 - 40 };
	obj->texpos = { 80,0 };
	obj->texHW = { 80,80 };
	obj->texprivot = { 40,40 };
}