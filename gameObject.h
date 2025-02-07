#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class Scene;

class GameObject
{
protected:

	bool     m_Destroy = false;
	bool     m_IsEnabled = false;
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale    = XMFLOAT3(1.0f, 1.0f, 1.0f);
	float m_ScaleCoefficient = 1.0f;
	Scene* m_CurrentScene = nullptr;

public:
	GameObject(Scene* scene) : m_CurrentScene(scene) {}
	virtual ~GameObject() {}

	virtual void Init() = 0; //純粋仮想関数
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	XMFLOAT3 GetPosition() { return m_Position ; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	XMFLOAT3 GetScale() { return m_Scale; }

	void SetEnabled(bool enabled) { m_IsEnabled = enabled; }

	void SetPositionX(float x) { m_Position.x = x; }
	void SetPositionY(float y) { m_Position.y = y; }
	void SetPosition(XMFLOAT3 position) { m_Position = position; }

	void SetRotation(float x, float y, float z) { m_Rotation = XMFLOAT3(x, y, z); }
	void SetRotationY(float y) { m_Rotation.y = y; }
	void SetRotation(XMFLOAT3 rotation) { m_Rotation = rotation; }

	void SetScale(float x, float y, float z) { m_Scale = XMFLOAT3(x, y, z); }
	void SetScale   (XMFLOAT3 scale) { m_Scale = scale; }
	void SetScaleCoefficient(float n) { m_ScaleCoefficient = n; }
	void SetDestroy() { m_Destroy = true; }


	float GetScaleCoefficient() { return m_ScaleCoefficient; }
	bool GetEnabled() const { return m_IsEnabled; }

	void SetScene(Scene* scene) { m_CurrentScene = scene; };
	Scene* GetScene() { return m_CurrentScene; };


	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else 
		{
			return false;
		}
	}

	XMFLOAT3 GetForward() //前方向ベクトル取得
	{
		//オイラー角から回転行列を生成
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw
		(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[2]);
		return forward;
	}

	XMFLOAT3 GetRight() {
		// オイラー角から回転行列を生成
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 right;
		XMStoreFloat3(&right, rotationMatrix.r[0]);			// マトリックスの1行目はX方向のVector
		return right;
	}
};