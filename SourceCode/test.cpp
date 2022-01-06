#include"all.h"
#define GROUND_Y 630
// YOYOYOYOOYOYYYOOYOYOYYOOYOYOOYYYOYOO

int test_state;
int test_timer;
int D;
OBJ2D portal;
OBJ2D ground;
OBJ2D player;
OBJ2D rect1;
OBJ2D rect3;
OBJ2D rect2[BLOCK_MAX];

void test_init()
{
	test_state = 0;
	test_timer = 0;
}
void test_deinit()
{

}
void test_update()
{
	switch (test_state)
	{
	case 0:
		test_state++;
	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);
		portal.pos = {125,50 };
		player.pos = { SCREEN_W/2,GROUND_Y };
		ground.pos = { 0,720-50 };
		rect1.pos = { 100,150 };
		test_state++;
	case 2:
		
		//if (test_timer % 120 == 0)
		//{
		//	D = rand() % 3 + 1;
		//	rect1.pos.x = D * 300 + 100;
		//}
		if (STATE(0) & PAD_RIGHT)
		{
			player.pos.x += 5;
		}
		if (STATE(0) & PAD_LEFT)
		{
			player.pos.x -= 5;
		}
		if (player.pos.x < 0)
			player.pos.x = 0;
		if (player.pos.x+50 > SCREEN_W)
			player.pos.x = SCREEN_W-50;
		break;
	}
	test_timer++;

}
void test_render()
{
	GameLib::clear(0, 0, 0);
	primitive::rect(portal.pos.x, portal.pos.y, 30, 30, 0, 0, 0, 0.5f, 1, 0);

	primitive::rect(rect1.pos.x, rect1.pos.y, 75, 75, 0, 0, 0, 0.5f, 0, 1);
	primitive::rect(ground.pos.x, ground.pos.y, SCREEN_W, 50, 0, 0, 0, 0.2f,0, 1);
	primitive::rect(player.pos.x, player.pos.y, 50, 50, 0, 0, 0, 0.3f, 0, 1);


}