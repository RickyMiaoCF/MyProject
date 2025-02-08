#pragma once

class Scene;

class SceneCheck
{
private:

	static SceneCheck m_Instance;

	SceneCheck() {};
	~SceneCheck() {};

	Scene* m_CurScene;

public:


	static SceneCheck& GetInstance() { return m_Instance; };

	void SetCurScene(Scene* curScene) { m_CurScene = curScene; };
	Scene* getCurScene() const { return m_CurScene; }

	void SetC();
};

