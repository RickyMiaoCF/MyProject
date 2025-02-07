#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"
#include "input.h"
#include "mouse.h"


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
    

    if (Input::GetKeyPress('I')) {
        m_Rotation.z += 0.5f; // 向上平移
    }
    if (Input::GetKeyPress('K')) {
        m_Rotation.z -= 0.5f; // 向下平移
    }
    if (Input::GetKeyPress('J')) {
        m_Rotation.x -= 0.5f; // 向左平移
    }
    if (Input::GetKeyPress('L')) {
        m_Rotation.x += 0.5f; // 向右平移
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

void Camera::RotateTarget(const XMFLOAT2& angle)
{
    // 将角度转换为弧度
    float yaw = XMConvertToRadians(angle.x);  // 水平旋转
    float pitch = XMConvertToRadians(angle.y);  // 垂直旋转

    // 1. 计算从相机位置指向目标的向量 (targetDir)
    XMVECTOR cameraPos = XMLoadFloat3(&m_Position);
    XMVECTOR cameraTarget = XMLoadFloat3(&m_Target);
    XMVECTOR targetDir = XMVectorSubtract(cameraTarget, cameraPos);

    // 2. 计算绕 Y 轴 (Yaw) 和 X 轴 (Pitch) 的旋转矩阵
    //    注意：旋转矩阵的乘法顺序会影响结果，通常先 Yaw 再 Pitch（或反之）实现不同的操控手感
    XMMATRIX rotY = XMMatrixRotationY(yaw);
    XMMATRIX rotX = XMMatrixRotationX(pitch);

    // 这里选择“先 Yaw 后 Pitch” 的顺序
    XMMATRIX matRot = XMMatrixMultiply(rotY, rotX);

    // 3. 使用旋转矩阵变换目标向量
    targetDir = XMVector3TransformNormal(targetDir, matRot);

    // 4. 计算新的目标位置：相机位置 + 旋转后的方向向量
    cameraTarget = XMVectorAdd(cameraPos, targetDir);
    XMStoreFloat3(&m_Target, cameraTarget);
}
