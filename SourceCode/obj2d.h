#ifndef OBJ2D_H
#define OBJ2D_H
struct OBJ2D
{
	VECTOR2 pos;
	VECTOR2 speed;
	VECTOR2 size;
	VECTOR2 pivot;
	VECTOR4 color;
	bool exist;
	int animeno;
	int color_count;
};
#endif // !OBJ2D_H

