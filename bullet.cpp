#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "scene.h"
#include "modelRenderer.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"


void Bullet::Init()
{
	m_Position = XMFLOAT3(-5.0f, 2.0f, 5.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\bullet.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	Scene* scene;
	scene = Manager::GetScene();
	forward = scene->GetGameObject<Player>()->GetForward();

}

void Bullet::Uninit()
{
	delete m_Component;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void Bullet::Update()
{
	Scene* scene;
	scene = Manager::GetScene();
	Score* score = scene->GetGameObject<Score>();
	//m_Position.z += 0.1f;
	if (m_Position.z > 100.0f)
	{
		SetDestroy();
		Explosion* explosion = scene->AddGameObject<Explosion>(WORLD);
		explosion->SetPosition(XMFLOAT3(m_Position.x, m_Position.y - 3.5f, m_Position.z));
	}

	std::vector<Enemy*> enemyList = scene->GetGameObjectList<Enemy>();
	for (auto enemy : enemyList)
	{
		XMFLOAT3 enemyPosition = enemy->GetPosition();

		XMFLOAT3 direction;
		direction.x = enemyPosition.x - m_Position.x;
		direction.y = enemyPosition.y - m_Position.y;
		direction.z = enemyPosition.z - m_Position.z;

		float length;
		length = sqrtf(direction.x * direction.x
			+ direction.y * direction.y
			+ direction.z * direction.z);
		if (length < 1.5f)
		{
			SetDestroy();
			enemy->SetDestroy();
			Explosion* explosion = scene->AddGameObject<Explosion>(WORLD);
			explosion->SetPosition(XMFLOAT3(m_Position.x, m_Position.y - 3.5f, m_Position.z));
			score->AddScore(3);
		}
	}
	m_Position.x += forward.x * 0.5f;
	m_Position.y += forward.y * 0.5f;
	m_Position.z += forward.z * 0.5f;
}

void Bullet::Draw()

{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}