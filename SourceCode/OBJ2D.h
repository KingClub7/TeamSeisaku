
class OBJ2D
{
public:
	VECTOR2 pos;
	VECTOR2 speed ;
	VECTOR2 texpos;//����I�ʎq
	VECTOR2 texHW;//����I����
	VECTOR2 texprivot;//��y
	VECTOR2 HW;//����
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