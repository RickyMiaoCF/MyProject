#pragma once
#include "gameObject.h"

class Camera : public GameObject
{
private:
	XMFLOAT3 m_Target{};
	XMFLOAT4X4 m_ViewMatrix{};

public:
	Camera(Scene* scene) :GameObject(scene) {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void RotateTarget(const XMFLOAT2& angle);
	XMVECTOR CamDir();
	XMMATRIX GetViewMatrix() { return XMLoadFloat4x4 (&m_ViewMatrix); }
};

