#pragma once
#include "gameObject.h"
#include "component.h"


class Sky : public GameObject
{
private:

	Component* m_Component{};

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:

	Sky(Scene* scene) :GameObject(scene) {}

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};