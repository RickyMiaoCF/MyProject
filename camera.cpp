#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"
#include"input.h"


void Camera::Init()
{
	m_Position = XMFLOAT3(0.0f, 10.0f, -40.0f);
	m_Target = XMFLOAT3(0.0f, 0.0f, 0.0f); 
   
    //Scene* scene = Manager::GetScene();

    //Player* player = scene->GetGameObject<Player>();
    //m_Target = player->GetPosition(); // 目标位置基于玩家位置
    //m_Target.y = 13.0f; // 固定初始高度
    // m_Position = XMFLOAT3(m_Target.x, 10.0f, m_Target.z - 20.0f);

}

void Camera::Uninit()
{

}

void Camera::Update()
{

    static bool m_CircularMode = false; // 记录当前是否处于圆周运动模式
    // 按键处理
    if (Input::GetKeyPress('I')) {
        m_Target.y += 0.5f; // 向上平移
    }
    if (Input::GetKeyPress('K')) {
        m_Target.y -= 0.5f; // 向下平移
    }
    if (Input::GetKeyPress('J')) {
        m_Target.x -= 0.5f; // 向左平移
    }
    if (Input::GetKeyPress('L')) {
        m_Target.x += 0.5f; // 向右平移
    }
    if (Input::GetKeyPress('N')) {
        m_CircularMode = false; // 退出圆周运动模式
        XMFLOAT3 forward = GetForward();
        m_Position.x += forward.x * 0.5f; // 靠近目标
        m_Position.y += forward.y * 0.5f;
        m_Position.z += forward.z * 0.5f;
    }
    if (Input::GetKeyPress('M')) {
        m_CircularMode = false; // 退出圆周运动模式
        XMFLOAT3 forward = GetForward();
        m_Position.x -= forward.x * 0.5f; // 远离目标
        m_Position.y -= forward.y * 0.5f;
        m_Position.z -= forward.z * 0.5f;
    }
    if (Input::GetKeyPress('U')) {
        m_CircularMode = true; // 开启圆周运动模式
        m_Rotation.y -= 0.05f; // 左旋
    }
    if (Input::GetKeyPress('O')) {
        m_CircularMode = true; // 开启圆周运动模式
        m_Rotation.y += 0.05f; // 右旋
    }

    // 如果处于圆周运动模式，更新摄像机的位置
    if (m_CircularMode) {
        m_Position.x = m_Target.x - sinf(m_Rotation.y) * 20.0f;
        m_Position.z = m_Target.z - cosf(m_Rotation.y) * 20.0f;
        m_Position.y = 10.0f; // 固定高度
    }
}

	//Scene* scene;
	//scene = Manager::GetScene();

	//Player* player;
	//player = scene->GetGameObject<Player>();

	//m_Target = player->GetPosition();
	//m_Target.y = 13.0f;

	//m_Position = XMFLOAT3(m_Target.x - 0.0f, 10.0f, m_Target.z -20.0f);
	//XMFLOAT3 forward = GetForward();

	//if (true)
	//{

	//}

	//if (Input::GetKeyPress('U'))
	//{
	//	m_Rotation.x -= 0.05f;

	//}
	//if (Input::GetKeyPress('O'))
	//{
	//	m_Rotation.x += 0.05f;

	//}
	////m_Position.x = m_Target.x - sinf(m_Rotation.x) * 3.0f;
	////m_Position.y = m_Target.y - cosf(m_Rotation.y) * 3.0f;


//}
void Camera::Draw()
{
	//ビューマトリクス設定
	XMFLOAT3 up{ 0.0f, 2.0f, 0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_Target), XMLoadFloat3(&up));
	
	Renderer::SetViewMatrix(viewMatrix);
	
	XMStoreFloat4x4(&m_ViewMatrix, viewMatrix);
	
	//ブロジェクションマトリクス設定
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	
	Renderer::SetProjectionMatrix(projectionMatrix);
}