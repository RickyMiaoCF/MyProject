#pragma once
#include "gameObject.h"
#include "componentsManager.h"
#include <string>


class Player : public GameObject
{
private:

	Component* m_Component{};
	ComponentsManager* m_ComponentsManager{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	std::string m_AnimationName{};

	float m_TargetRotationY{};
	float m_TurnSpeed = 0.01f;

	std::string m_AnimationName1{};
	std::string m_AnimationName2{};
	float m_AnimationBlendRatio = 0;
	
	
	
	int m_AnimationFrame = 0;

	XMFLOAT3 m_Velocity{};
	XMFLOAT4 m_Quaternion{};

	class Audio* m_SE{};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	ComponentsManager* GetComponentsManager() { return	m_ComponentsManager; }
};