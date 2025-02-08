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

    float moveSpeed = 0.3f;
    
    // 1) 先获取当前相机的“前方向”
    XMVECTOR forward = CamDir();
    forward = XMVector3Normalize(forward); // 归一化

    // 2) 计算“右方向”：up = (0,1,0) 或根据需要
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMVECTOR right = XMVector3Cross(up, forward);
    right = XMVector3Normalize(right);

    // 3) 读取相机当前位置（以便加上移动量）
    XMVECTOR camPos = XMLoadFloat3(&m_Position);

    // ————— 根据按键来移动相机 —————
    if (Input::GetKeyPress('I')) {
        // 沿前方向移动
        camPos = XMVectorAdd(camPos, XMVectorScale(forward, moveSpeed));
    }
    if (Input::GetKeyPress('K')) {
        // 后退：前方向取负
        camPos = XMVectorSubtract(camPos, XMVectorScale(forward, moveSpeed));
    }
    if (Input::GetKeyPress('J')) {
        // 左移：右方向取负
        camPos = XMVectorSubtract(camPos, XMVectorScale(right, moveSpeed));
    }
    if (Input::GetKeyPress('L')) {
        // 右移：沿 right 向量正方向
        camPos = XMVectorAdd(camPos, XMVectorScale(right, moveSpeed));
    }
        
    XMStoreFloat3(&m_Position, camPos);

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

XMVECTOR Camera::CamDir()
{
    // 1. 计算从相机位置指向目标的向量 (targetDir)
    XMVECTOR cameraPos = XMLoadFloat3(&m_Position);
    XMVECTOR cameraTarget = XMLoadFloat3(&m_Target);
    XMVECTOR targetDir = XMVectorSubtract(cameraTarget, cameraPos);
    return targetDir;
}