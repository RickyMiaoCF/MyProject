#include "gameObject.h"
#include "componentsManager.h"
//#include "wave.h"
#include "floatingSample.h"
#include "floatingPlate.h"
//#include "game.h"
#include "debug.h"

//Wave* g_Wave = nullptr;

#define SAMPLE_COUNT (4)

void FloatingPlate::Init()
{
	m_Manager->GetParentObj()->GetPosition();
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
	static XMFLOAT3		parentPos{};
	static float	tempX = 0.0f;
	static float	tempY = 0.0f;
	static float	tempZ = 0.0f;



	//サンプルのポジションを更新
	parentPos = m_Manager->GetParentObj()->GetPosition();
	m_Pos = parentPos;

	parentPos = m_Manager->GetParentObj()->GetPosition();
	m_Pos = parentPos;

	float offsets[4][2] = {
		{-0.5, -0.5},
		{0.5,  -0.5},
		{-0.5,  0.5},
		{0.5,   0.5}
	};
	//四角のポジションデータを算出
	for (int i = 0; i < SAMPLE_COUNT; i++) {
		float tempX = m_Pos.x + (m_Width * offsets[i][0]);
		float tempZ = m_Pos.z + (m_Length * offsets[i][1]);
		//当ボジションの波の高さを算出
		/*float tempY = g_Wave->getHeight(XMFLOAT3(tempX, m_Pos.y, tempZ));*/
		m_Samples[i]->SetPos(XMFLOAT3(tempX, tempY, tempZ));

	}

	DEBUG_VAR(m_Samples[0]->GetPos());
	DEBUG_VAR(m_Samples[1]->GetPos());
	DEBUG_VAR(m_Samples[2]->GetPos());
	DEBUG_VAR(m_Samples[3]->GetPos());
}

