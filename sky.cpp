#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sky.h"
#include "modelRenderer.h"
#include "input.h"
#include "scene.h"


void Sky::Init()
{
	m_Position.y = 49.69f;
	m_ScaleCoefficient = -40.0f;
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\sunset.obj");
	m_Component->SetEnabled(true);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
}

void Sky::Uninit()
{
	delete m_Component;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void Sky::Update()
{
	m_Component->Update();
	Scene* scene;
	scene = Manager::GetScene();


}

void Sky::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x*(1.0f+m_ScaleCoefficient*0.01f), m_Scale.y*(1.0f + m_ScaleCoefficient * 0.01f), m_Scale.z* (1.0f + m_ScaleCoefficient * 0.01f));
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}