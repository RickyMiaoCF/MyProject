#pragma once
#include "gameObject.h"

class MeshField : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};				// インデックスBuffer

	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	VERTEX_3D m_Vertex[21][21];
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	float getHeight(XMFLOAT3 position);
};