#include"all.h"
Scene* pScene;
SceneGame scenegame;
SceneTitle scenetitle;
GameOver sceneover;
SceneClear sceneclear;
SceneRule scenerule;
Scene* scene_label[] =
{
	&scenetitle,
	&scenegame,
	&sceneover,
	&sceneclear,
	&scenerule
};
int nextSceneNo = -1;
void setScene(int scene)
{
	if (scene >= SCENE_MAX)
		return;
	nextSceneNo = scene;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameLib::init(L"No.1332 presentB", 1280, 720);
	audio_init();
	setScene(SCENE_TITLE);
	while (GameLib::gameLoop())
	{
		
		music::update();
		GameLib::input::update();
		
		

		if (nextSceneNo != -1)
		{
			pScene = scene_label[nextSceneNo];
			pScene->init();
			nextSceneNo = -1;
		}
		pScene->update();
		pScene->render();
		GameLib::debug::display(1.0f, 1.0f, 1.0f, 1, 1);
		GameLib::present(1, 0);

	}

	GameLib::uninit();
	
	pScene->deinit();
	return 0;
}