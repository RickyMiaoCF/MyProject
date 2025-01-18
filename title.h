#pragma once
#include "scene.h"
#include <chrono>

class Title : public Scene
{
private:

	bool m_startFadeOut;
	float m_DiffuseColor; // 色の強さ
	std::chrono::steady_clock::time_point m_LastUpdateTime; // 最終更新時刻

public:
	void Init() override;
	void Update() override;
};