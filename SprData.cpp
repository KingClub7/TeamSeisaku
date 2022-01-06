#include"All.h"
TEXTURE_NORMAL texBack00("./Image/Back00.bmp");
TEXTURE_BLACK  texSpr000("./Image/SPR000.bmp");

LOAD_TEXTURE load_texture = {
	&texBack00,
	&texSpr000,
};

SPRITE_LEFTTOP spr_back(&texBack00, 0, 0, 640, 480);
SPRITE_CENTER  spr_player(&texSpr000, 128, 0, 64, 32);
SPRITE_CENTER  spr_enemy(&texSpr000, 96, 96, 32, 32);

//kankeinashi