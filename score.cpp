#include "main.h"
#include "renderer.h"
#include "audio.h"
#include "input.h"

void Score::Init()
{
	m_Position = XMFLOAT3(150.0f, 50.0f, 0.0f);
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(m_Position.x-50.0f, m_Position.y - 50.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(m_Position.x + 50.0f, m_Position.y - 50.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(m_Position.x - 50.0f, m_Position.y + 50.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(m_Position.x + 50.0f, m_Position.y + 50.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	
	//↓改正（アニメーション関連）
	bd.Usage = D3D11_USAGE_DYNAMIC;

	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	//↓改正（アニメーション関連）
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\number.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	
	m_Count = 0;

}

void Score::Uninit()
{

	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Score::Update()
{


}

void Score::Draw()
{
	int score = m_Count;
	const int maxDigits = 3;
	int digits[maxDigits] = { 0 };

	for (int i = 0; i < maxDigits; i++)
	{
		digits[i] = score % 10;
		score /= 10;
	}

	for (int i = 0; i < maxDigits; i++)
	{
		int number = digits[maxDigits - i - 1];
		float x = (number % 5) * (1.0f / 5);
		float y = (number / 5) * (1.0f / 5);

		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
		float offset = 100.0f * i;
		vertex[0].Position = XMFLOAT3(m_Position.x - 50.0f + offset, m_Position.y - 50.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(x, y);

		vertex[1].Position = XMFLOAT3(m_Position.x + 50.0f + offset, m_Position.y - 50.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(x + 0.2f, y);

		vertex[2].Position = XMFLOAT3(m_Position.x - 50.0f + offset, m_Position.y + 50.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(x, y + 0.2f);

		vertex[3].Position = XMFLOAT3(m_Position.x + 50.0f + offset, m_Position.y + 50.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(x + 0.2f, y + 0.2f);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
		Renderer::SetWorldViewProjection2D();

		UINT stride = sizeof(VERTEX_3D);
		UINT offset_vb = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset_vb);

		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

}

void Score::AddScore(int Count)
{
	m_Count+= Count;
}
