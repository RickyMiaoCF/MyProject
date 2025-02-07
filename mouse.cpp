#include "mouse.h"
#include "camera.h"
#include "debug.h"

Mouse Mouse::m_Instance;//C++で、すべてのstaticメンバーを外部で宣言する必要がある

Camera* g_Cam={};
XMFLOAT2 g_CamRot={};

void Mouse::Init()
{

}

void Mouse::Update()
{

    if (m_RDown && g_Cam)
    {
        // 计算鼠标移动量
        XMFLOAT2 delta = MoveCal();

        g_CamRot = XMFLOAT2(0.0f, 0.0f);

        // 定义旋转灵敏度，具体值可根据需要调整
        const float sensitivity = 0.1f;

        // 根据鼠标移动量更新摄像机旋转
        g_CamRot.x += delta.x * sensitivity;
        g_CamRot.y += delta.y * sensitivity;


        // 可选：限制俯仰角（pitch）的范围（例如限制在 -90° 到 90°，这里以弧度表示）
        if (g_CamRot.x > +XM_PIDIV2) g_CamRot.x = +XM_PIDIV2;
        if (g_CamRot.x < -XM_PIDIV2) g_CamRot.x = -XM_PIDIV2;

        g_Cam->RotateTarget(g_CamRot);
    }

    // 每帧结束时，无论是否有鼠标移动，都将前一帧坐标更新为当前坐标，
    // 这样下一帧如果没有新的 WM_MOUSEMOVE 事件，delta 将为零
    m_PreX = m_CurX;
    m_PreY = m_CurY;

    DEBUG_VAR(m_CurX);
    DEBUG_VAR(m_CurY);
    DEBUG_VAR(m_PreX);
    DEBUG_VAR(m_PreY);
}

void Mouse::SetCam(Camera* cam)
{
	g_Cam = cam;
}


