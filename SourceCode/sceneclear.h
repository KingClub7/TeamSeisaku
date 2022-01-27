
class SceneClear :public Scene
{
	int state;
	int timer;
	int animeno;
	Sprite* clear;
public:
	void init();
	void update();
	void render();
	void deinit();
};