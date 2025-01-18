#pragma once
#include "scene.h"
#include "gameObject.h"

class Manager
{
private:
	static Scene* m_Scene;
	static Scene* m_NextScene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() { return m_Scene; };

	template <typename T> //テンプレート関数
	static void SetScene()
	{	

		m_NextScene = new T();
		//if (m_Scene)
		//{
		//	m_Scene->Uninit();
		//	delete m_Scene;
		//}
		//m_Scene = new T();
		//m_Scene->Init();
	};

};