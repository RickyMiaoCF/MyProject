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
#include "MeshField.h"
#include "debug.h"
#include "visualBox.h"
#include "floatingPlate.h"

#define ROT_ANKLE_MAX		(120.0f)



void Player::Init()
{
	m_Position.y = -1.0f;
	m_ComponentsManager = new ComponentsManager(this);
	
	m_ComponentsManager->AddComponent<ModelRenderer>();
	m_ComponentsManager->GetComponent<ModelRenderer>()->Load("asset\\model\\ship_pinnace_2k.obj");
	//m_ComponentsManager->AddComponent<VisualBox>();
	/*m_ComponentsManager->AddComponent<FloatingPlate>();*/
	m_ComponentsManager->AddComponent<FloatingPlate>()->SetSize(20.0f, 30.0f);
	/*m_ComponentsManager->GetComponent<ModelRenderer>()->SetEnabled(false);*/
	//m_Component = new ModelRenderer(this);
	////((ModelRenderer*)m_Component)->Load("asset\\model\\19882_Go-fast_Boat_v1.obj");
	//((ModelRenderer*)m_Component)->Load("asset\\model\\ship_pinnace_2k.obj");

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


	DEBUG_VAR(m_TargetRotationY);

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

	//円柱との衝突判定
	/*auto cylinderList = scene->GetGameObjectList<Cylinder>();
	for (Cylinder* cylinder : cylinderList)
	{
		XMFLOAT3 cylinderPosition = cylinder->GetPosition();
		XMFLOAT3 cylinderScale = cylinder->GetScale();

		XMFLOAT3 direction;
		direction.x = cylinderPosition.x - m_Position.x;
		direction.y = cylinderPosition.y - m_Position.y;
		direction.z = cylinderPosition.z - m_Position.z;
		float length;
		length = sqrtf(direction.x * direction.x
			+ direction.z * direction.z);
		if (length < cylinderScale.x)
		{
			if (-direction.y > cylinderScale.y - 0.5f)
			{
				groundHeight = cylinderPosition.y + cylinderScale.y;
			}
			else
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
		}
	}*/
	////箱との衝突判定
	//auto boxList = scene->GetGameObjectList<Box>();
	//for (Box* box : boxList)
	//{
	//	XMFLOAT3 boxPosition = box->GetPosition();
	//	XMFLOAT3 boxScale =    box->GetScale();

	//	XMFLOAT3 direction;
	//	direction.x = boxPosition.x - m_Position.x;
	//	direction.y = boxPosition.y - m_Position.y;
	//	direction.z = boxPosition.z - m_Position.z;
	//	float length;
	//	length = sqrtf(direction.x * direction.x
	//		+ direction.z * direction.z);


	//	if (-direction.y > boxScale.y - 0.5f)
	//	{
	//		groundHeight = boxPosition.y + boxScale.y;
	//	}
	//	else
	//	{
	//		m_Position.x = oldPosition.x;
	//		m_Position.z = oldPosition.z;
	//	}
	//	}
	//}



	//木との衝突判定
	//auto treeList = scene->GetGameObjectList<Tree>();
	//for (Tree* tree : treeList)
	//{
	//	XMFLOAT3 treePosition = tree->GetPosition();
	//	XMFLOAT3 treeScale = tree->GetScale();

	//	XMFLOAT3 direction;
	//	direction.x = treePosition.x - m_Position.x;
	//	direction.y = treePosition.y - m_Position.y;
	//	direction.z = treePosition.z - m_Position.z;
	//	float length;
	//	length = sqrtf(direction.x * direction.x
	//		+ direction.z * direction.z);
	//	if (length < treeScale.x + 1.0f)
	//	{
	//		{
	//			m_Position.x = oldPosition.x;
	//			m_Position.z = oldPosition.z;
	//		}
	//	}
	//}
	//地面との衝突判定
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

	m_ComponentsManager->Draw();
	/*m_Component->Draw();*/
}