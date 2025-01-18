#pragma once
#include <DirectXMath.h>
using namespace DirectX;
class Component
{
protected:

	class GameObject* m_GameObject = nullptr;
	class ComponentsManager* m_Manager = nullptr;
	bool m_Destroy = false;

	bool m_IsEnabled = false;
	float m_Width{};	//x
	float m_Height{};	//y
	float m_Length{};	//z
	XMFLOAT3 m_Position{};
	XMFLOAT3 m_Rotation{};
	XMFLOAT3 m_Scale{};


public:
	Component() = delete;
	Component(GameObject* Object) { m_GameObject = Object; }
	Component(ComponentsManager* manager) { m_Manager = manager; };
	virtual ~Component() {}

	virtual void Init() {}; //仮想関数
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};

	void SetEnabled(bool enabled) { m_IsEnabled = enabled; }
	void SetWidth(float width) { m_Width = width; }
	void SetHeight(float height) { m_Height = height; }
	void SetLength(float length) { m_Length = length; }
	void SetPosition(const XMFLOAT3& position) { m_Position = position; }
	void SetRotation(const XMFLOAT3& rotation) { m_Rotation = rotation; }
	void SetScale(const XMFLOAT3& scale) { m_Scale = scale; }

	void SetPosition(float x, float y, float z) { m_Position = XMFLOAT3(x, y, z); }
	void SetRotation(float x, float y, float z) { m_Rotation = XMFLOAT3(x, y, z); }
	void SetScale(float x, float y, float z) { m_Scale = XMFLOAT3(x, y, z); }

	bool GetEnabled() const { return m_IsEnabled; }
	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
	float GetLength() const { return m_Length; }
	XMFLOAT3 GetPosition() const { return m_Position; }
	XMFLOAT3 GetRotation() const { return m_Rotation; }
	XMFLOAT3 GetScale() const { return m_Scale; }

	//シングル変数の調整
	float GetPositionX() const { return m_Position.x; }
	float GetPositionY() const { return m_Position.y; }
	float GetPositionZ() const { return m_Position.z; }

	float GetRotationX() const { return m_Rotation.x; }
	float GetRotationY() const { return m_Rotation.y; }
	float GetRotationZ() const { return m_Rotation.z; }

	float GetScaleX() const { return m_Scale.x; }
	float GetScaleY() const { return m_Scale.y; }
	float GetScaleZ() const { return m_Scale.z; }

	void SetDestroy() { m_Destroy = true; }

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

};