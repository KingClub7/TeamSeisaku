
class OBJ2D
{
public:
	VECTOR2 pos;
	VECTOR2 speed ;
	VECTOR2 texpos;//圖上的位子
	VECTOR2 texHW;//圖上的長�ｪ
	VECTOR2 texprivot;//基準點
	VECTOR2 HW;//長�ｪ
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