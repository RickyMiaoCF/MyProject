#pragma once
#include "gameObject.h"

class Camera : public GameObject
{
private:
	XMFLOAT3 m_Target{};
	XMFLOAT4X4 m_ViewMatrix{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMMATRIX GetViewMatrix() { return XMLoadFloat4x4 (&m_ViewMatrix); }
};

