
class OBJ2D
{
public:
	VECTOR2 pos;
	VECTOR2 speed ;
	VECTOR2 texpos;//š¤ã“IˆÊq
	VECTOR2 texHW;//š¤ã“I’·úª
	VECTOR2 texprivot;//Šî€êy
	VECTOR2 HW;//’·úª
	Sprite* spr;
	float alpha;
	int effectTimer;
	int state;
	int animeno;
	int jumpcount;
	int bombcount;
	int timer;
	VECTOR2 size;
	OBJ2D();
	void bomb_init(OBJ2D*obj);
};