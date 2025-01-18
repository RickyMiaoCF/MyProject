#include "main.h"
#include "gameObject.h"
#include "componentsManager.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "visualBox.h"
#include "debug.h"

static float offsets[8][3] = {
		{-0.5,-0.5,-0.5},
		{ 0.5,-0.5,-0.5},
		{-0.5,-0.5, 0.5},
		{ 0.5,-0.5, 0.5},
		{-0.5, 0.5,-0.5},
		{ 0.5, 0.5,-0.5},
		{-0.5, 0.5, 0.5},
		{ 0.5, 0.5, 0.5},
	};

void VisualBox::Init()
{

	m_IsEnabled = true;

	m_Parent = m_Manager->GetParentObj();

	m_Position = m_Parent->GetPosition();

	m_Rotation = m_Parent->GetRotation();

	m_Scale = XMFLOAT3(1.0f,1.0f, 1.0f);

	m_Height = 10.0f;

	m_Width = 10.0f;

	m_Length = 10.0f;

	//頂点位置のオフセット


	//8つの頂点を設定
	for (int i = 0; i < BOX_VERTEX_NUM; i++)
	{
		m_Vertex[i].Position = XMFLOAT3((m_Position.x + m_Height * offsets[i][0]) * m_Scale.x, (m_Position.y + m_Width * offsets[i][1]) * m_Scale.y,
			(m_Position.z + m_Length * offsets[i][2]) * m_Scale.z);

		m_Vertex[i].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_Vertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Vertex[i].TexCoord = XMFLOAT2(0.0f, 0.0f);
	}


	// ボックスの辺(12辺)のインデックス
	unsigned int indices[] = {
		0, 1, 1, 3, 3, 2, 2, 0, // 底面辺
		4, 5, 5, 7, 7, 6, 6, 4, // 上面辺
		0, 4, 1, 5, 2, 6, 3, 7  // サイド辺
	};

	// 頂点バッファを作る
	D3D11_BUFFER_DESC vbd = {};
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(m_Vertex);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = m_Vertex;

	Renderer::GetDevice()->CreateBuffer(&vbd, &vertexData, &m_VertexBuffer);

	// インデックスバッファを作る
	D3D11_BUFFER_DESC ibd = {};
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(indices);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData = {};
	ZeroMemory(&indexData, sizeof(indexData));
	indexData.pSysMem = indices;

	Renderer::GetDevice()->CreateBuffer(&ibd, &indexData, &m_IndexBuffer);

}

void VisualBox::Uninit()
{
	m_IsEnabled = false;
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();

}

void VisualBox::Update() {

	m_Position = m_Parent->GetPosition();
	m_Rotation = m_Parent->GetRotation();

	for (int i = 0; i < BOX_VERTEX_NUM; i++)
	{
		m_Vertex[i].Position = XMFLOAT3((m_Position.x + m_Height * offsets[i][0]) * m_Scale.x, (m_Position.y + m_Width * offsets[i][1]) * m_Scale.y,
			(m_Position.z + m_Length * offsets[i][2]) * m_Scale.z);
	}

	D3D11_MAPPED_SUBRESOURCE msr;
	HRESULT hr = Renderer::GetDeviceContext()->Map(
		m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr
	);
	if (SUCCEEDED(hr)) {
		memcpy(msr.pData, m_Vertex, sizeof(m_Vertex)); 
		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);   
	}

	DEBUG_VAR(m_IsEnabled);
	DEBUG_VAR(m_Height);

}

void VisualBox::Draw() {
	if (!m_IsEnabled) return;

	 /*ワールドマトリクス設定*/
	XMMATRIX world, rot, trans;
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = rot * trans;
	Renderer::SetWorldMatrix(world);

	// 緑色線をセット
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	Renderer::SetMaterial(material);

	// 頂点繋げってボックスを描画
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	Renderer::GetDeviceContext()->DrawIndexed(24, 0, 0);
}


