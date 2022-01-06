#include "all.h"

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	GameLib::init(L"JUDGE", SCREEN_W, SCREEN_H);
	test_init();
	while (GameLib::gameLoop())
	{
		input::update();
		test_update();
		test_render();
		debug::display(1.0f, 1.0f, 1.0f, 1, 1);
		GameLib::present(1, 0);
	}

	test_deinit();
	GameLib::uninit();
	return 0;
}