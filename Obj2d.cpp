#include "All.h"
Obj2d::Obj2d()
{
	data = 0;
	pos = { 0,0 };
}

void Obj2d::draw()
{
	if (data) GL::DrawSprite(pos.x, pos.y, data);
}
//‚¨‚İ‚­‚¶‹¥‚¾‚Á‚½‚æ’{¶
//ƒKƒ`ƒƒ‚Å80%‚ğ“ñ‰ñ‚à‚·‚è”²‚¯‚½‚æ’{¶