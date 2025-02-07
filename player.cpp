#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "audio.h"
#include "input.h"
#include "scene.h"
#include "result.h"
#include "debug.h"
#include "visualBox.h"
#include "floatingPlate.h"

#define ROT_ANKLE_MAX		(120.0f)

bool g_s = false;

void Player::Init()
{
	m_Position.y = -1.0f;
	m_ComponentsManager = new ComponentsManager(this);
	
	m_ComponentsManager->AddComponent<ModelRenderer>();
	m_ComponentsManager->GetComponent<ModelRenderer>()->Load("asset\\model\\ship_pinnace_2k.obj");
	m_ComponentsManager->AddComponent<VisualBox>();
	m_ComponentsManager->AddComponent<FloatingPlate>()->SetSize(20.0f, 30.0f);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	//SE
	m_SE = new Audio(this);
	m_SE->Load("asset\\audio\\Ak47GunShot.wav");
	//m_SE->Play(true);
	m_Quaternion.x = 0.0f;
	m_Quaternion.y = 0.0f;
	m_Quaternion.z = 0.0f;
	m_Quaternion.w = 1.0f;

	m_Scale = { 0.5f,0.5f,0.5f };
	
}

void Player::Uninit()
{
	m_ComponentsManager->Uninit();
	delete m_ComponentsManager;
	m_SE->Uninit();
	delete m_SE;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void Player::Update()
{
	m_ComponentsManager->Update();
	/*m_Component->Update();*/
	Scene* scene;
	scene = Manager::GetScene();
	XMFLOAT3 oldPosition = m_Position;
	/*m_Position.y = scene->GetGameObject<Wave>()->getHeight(m_Position);*/


	XMFLOAT3 forward = GetForward();
	XMFLOAT3 right = GetRight();

	DEBUG_VAR(m_Position);
	DEBUG_VAR(m_Rotation);

	XMFLOAT3 tempRot = m_ComponentsManager->GetComponent<FloatingPlate>()->GetRotation();

	m_Rotation.x = tempRot.x;
	m_Rotation.z = tempRot.z;
	

	//if (Input::GetKeyTrigger('K'))
	//{
	//	Bullet* bullet = scene->AddGameObject<Bullet>(1);
	//	bullet->SetPosition(m_Position);
	//	m_SE->Play(true);
	//}


	if (Input::GetKeyPress('W'))
	{
		//m_Position.z += 0.1f;
		m_Position.x += forward.x * 0.1f;
		m_Position.y += forward.y * 0.1f;
		m_Position.z += forward.z * 0.1f;

	}

	if (Input::GetKeyPress('V'))
	{
		g_s =! g_s;
	}

	if (Input::GetKeyPress('A'))
	{
		// 左回転
		m_TargetRotationY -= m_TurnSpeed;
	}
	if (Input::GetKeyPress('D'))
	{
		// 右回転
		m_TargetRotationY += m_TurnSpeed;
	}

	DEBUG_VAR(m_Position);

	// スムーズで回転
	float rotationStep = m_TurnSpeed * 0.8f; // 毎フレムの回転最大値，回転のスムーズを制御

	if (m_Rotation.y < m_TargetRotationY)
	{
		m_Rotation.y = std::min(m_Rotation.y + rotationStep, m_TargetRotationY);
	}
	else if (m_Rotation.y > m_TargetRotationY)
	{
		m_Rotation.y = std::max(m_Rotation.y - rotationStep, m_TargetRotationY);
	}


	//if (Input::GetKeyTrigger('J'))
	//{
	//	m_Velocity.y = 1.0f;
	//}

	//if (Input::GetKeyTrigger('E'))
	//{
	//	Bullet* bullet = scene->AddGameObject<Bullet>(WORLD);
	//	bullet->SetPosition(XMFLOAT3(m_Position.x, m_Position.y + 1.0f, m_Position.z));
	//	m_SE->Play();
	//	//scene->AddGameObject<Bullet>()->SetPosition(m_Position);
	//}


	//地面の高さ
	float groundHeight = 0.0f;

	if (m_Position.y < groundHeight)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}

}

void Player::Draw()
{
	//【NOTE】用.c_str()获得动画名字符串
	//((AnimationModel*)m_Component)->Update(m_AnimationName.c_str(), m_AnimationFrame);
	//((AnimationModel*)m_Component)->Update(m_AnimationName1.c_str(), m_AnimationFrame,
	//	m_AnimationName2.c_str(), m_AnimationFrame,
	//	m_AnimationBlendRatio);
	//m_AnimationFrame++;

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	/*DEBUG_VAR(scale);*/
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_Quaternion));
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	Renderer::ChangeRSWireframe(g_s);

	m_ComponentsManager->Draw();
	/*m_Component->Draw();*/
}


