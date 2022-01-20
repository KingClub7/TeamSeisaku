#pragma once
enum SceneLabel
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_OVER,
	SCENE_CLEAR,



	SCENE_MAX
};

extern int nextscene;
void setScene(int scene);