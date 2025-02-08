#pragma once
#include "gameObject.h"
#include "component.h"


class SkyR : public GameObject
{
private:

	Component* m_Component{};

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	UINT	      m_IndexCount = 0;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader*  m_PixelShader{};
	ID3D11InputLayout*  m_VertexLayout{};
	

public:

	SkyR(Scene* scene) :GameObject(scene) {}
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void CreateSkyBoxMesh();
};