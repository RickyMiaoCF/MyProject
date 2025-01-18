#pragma once
#include "scene.h"
#include <chrono> // 時間計測のため


class Game : public Scene
{

	/*static Game* m_Instance;*/

	//Game() {};

public:
	void Init() override;
	void Update() override;
	void Draw()	override;

	//static Game* GetGameScene()
	//{
	//	if (!m_Instance)
	//		m_Instance = new Game;
	//	
	//	return m_Instance;
	//};

};