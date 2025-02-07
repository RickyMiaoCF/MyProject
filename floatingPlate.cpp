#include "gameObject.h"
#include "componentsManager.h"
#include "wave.h"
#include "floatingSample.h"
#include "floatingPlate.h"
//#include "game.h"
#include "debug.h"
#include "scene.h"


#define SAMPLE_COUNT (4)

Wave* g_Wave;

void FloatingPlate::Init()
{
	m_Manager->GetParentObj()->GetPosition();
	g_Wave = m_Manager->GetParentObj()->GetScene()->GetGameObject<Wave>();
	m_Width = 0.0f;
	m_Length = 0.0f;

	for (int i = 0; i < SAMPLE_COUNT; i++)
	{
		m_Samples[i] = new FloatingSample;
	}
}

void FloatingPlate::Uninit()
{
	for (int i = 0; i < SAMPLE_COUNT; i++)
	{
		delete m_Samples[i];
		m_Samples[i] = nullptr;
	}
}

void FloatingPlate::Update()
{
    static XMFLOAT3 parentPos{};
    parentPos = m_Manager->GetParentObj()->GetPosition();
    m_Pos = parentPos;

    float offsets[4][2] = {
        {-0.5, -0.5},
        {0.5,  -0.5},
        {-0.5,  0.5},
        {0.5,   0.5}
    };

    XMFLOAT3 samplePos[4];

    // 计算每个采样点的水面高度
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        float tempX = m_Pos.x + (m_Width * offsets[i][0]);
        float tempZ = m_Pos.z + (m_Length * offsets[i][1]);
        float tempY = g_Wave->getHeight(XMFLOAT3(tempX, m_Pos.y, tempZ));
       /* float tempY = 0.0f;*/
        samplePos[i] = XMFLOAT3(tempX, tempY, tempZ);
        m_Samples[i]->SetPos(samplePos[i]);
    }

    // 计算法向量
    XMVECTOR P0 = XMLoadFloat3(&samplePos[0]);
    XMVECTOR P1 = XMLoadFloat3(&samplePos[1]);
    XMVECTOR P2 = XMLoadFloat3(&samplePos[2]);

    XMVECTOR v1 = XMVectorSubtract(P1, P0);
    XMVECTOR v2 = XMVectorSubtract(P2, P0);
    XMVECTOR normal = XMVector3Cross(v1, v2);
    normal = XMVector3Normalize(normal);

    // 计算 Pitch & Roll
    float pitch = atan2(normal.m128_f32[2], normal.m128_f32[1]); // z/y
    float roll = atan2(normal.m128_f32[0], normal.m128_f32[1]); // x/y

    // 设置旋转角度
    m_Rotation = XMFLOAT3(pitch, 0.0f, roll);

    DEBUG_VAR(m_Rotation);
}
